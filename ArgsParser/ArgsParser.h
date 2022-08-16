#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>
#include <cctype>
#include <functional>
#include <unordered_map>
#include <charconv>
#include "ArgsExceptions.h"
#include <iostream>
class ArgsParser
{
private:
    std::string_view pattern_;
    std::string_view args_;
    std::unordered_map<char, std::any> table_;
    
    void pattern_check(){
        constexpr bool supported_pattern[26] = {
            0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
        };
        std::function<void(const size_t)> predicator[4];
        predicator[0] = [this](const size_t idx){
            if(!std::islower(this->pattern_[idx]))
                throw InvalidPattern("Invalid Pattern: Invalid Option");
        };
        predicator[1] = [this](const size_t idx){
            if(this->pattern_[idx] != ':')
                throw InvalidPattern("Invalid Pattern: Colons Error");
        };
        predicator[2] = [this, &supported_pattern](const size_t idx){
            if(!std::islower(this->pattern_[idx]) || !supported_pattern[this->pattern_[idx] - 'a'])
                throw InvalidPattern("Invalid Pattern: Unsupproted Option Type");
        };
        predicator[3] = [this](const size_t idx){
            if(this->pattern_[idx] != ',')
                throw InvalidPattern("Invalid Pattern: Commas Error");
        };

        size_t mask = 0b11;
        for(int idx = 0; idx < pattern_.length(); ++idx){
            predicator[idx & mask](idx);     
        }
    }

    void arguments_check(){
        const int whitespaces[26] = {
            0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0
        };
        size_t idx = 0;

        auto check_whitespace = [this, &whitespaces](const size_t start, const size_t end){
            size_t idx = this->pattern_.find(this->args_[start]);
            if(idx == std::string_view::npos)
                throw InvalidArgument("Invalid Argument: Undefined  Argument");
            size_t type_idx = idx + 2;
            size_t length = end != std::string_view::npos ? end - start : end;
            size_t whitespace_cnt = end != std::string_view::npos ? 
                                    whitespaces[this->pattern_[type_idx] - 'a'] :
                                    whitespaces[this->pattern_[type_idx] - 'a'] - 1;
        
            std::string_view sub_str = this->args_.substr(start, length);

            auto cnt = std::count(sub_str.begin(), sub_str.end(), ' ');
            if(cnt != whitespace_cnt)
                    throw InvalidArgument("Invalid Argument: Wrong Number of Parameters");
            switch (this->pattern_[type_idx])
            {
            case 'b':
                this->table_[this->args_[start]] = std::make_any<bool>(true);
                break;
            case 'n':{
                auto value_str = sub_str.substr(2);
                auto last_whitespace = value_str.find_last_of(' ');
                if (last_whitespace != std::string_view::npos) {
                    value_str.remove_suffix(value_str.size() - last_whitespace);
                }
                int32_t value;
                if(std::from_chars(value_str.begin(), value_str.end(), value).ec != std::errc{}){
                    throw InvalidArgument("Invalid Argument: Unmatch type and argument");
                }
                this->table_[this->args_[start]] = std::make_any<int32_t>(value);
                break;
            }
            // case 's':
            //     break;
            default:
                break;
            }
            

        };

        while(idx != std::string_view::npos){
            size_t next_hyphen = args_.find('-', idx + 1);
            check_whitespace(idx + 1, next_hyphen);
            idx = next_hyphen;
        }
    }
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){
            pattern_check();
            arguments_check();
        }
    ~ArgsParser(){}
    
    bool getBoolean(const char option){
        return table_.find(option) != table_.end() ? true : false;
    }

    int32_t getNumber(const char option){
        if(table_.find(option) != table_.end()){
            return std::any_cast<int32_t>(table_[option]);
        }
        return 8080;
    }
};



#endif