#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>
#include <cctype>
#include <functional>
#include "ArgsExceptions.h"

class ArgsParser
{
private:
    std::string_view pattern_;
    std::string_view args_;
    
    
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
        static const int whitespaces[26] = {
            0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
            2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0
        };
        size_t idx = 0;
        auto get_args_whitespaces = [this](const char ch)->int{
            size_t idx = this->pattern_.find(ch);
            if(idx == std::string_view::npos)
                throw InvalidArgument("Invalid Argument: Undefined  Argument");
            return whitespaces[this->pattern_[idx + 2] - 'a'];
        };
        while(idx < args_.length()){
            size_t next_hyphen = args_.find('-', idx + 1);
            size_t whitespace_cnt = get_args_whitespaces(args_[idx + 1]);
            if (next_hyphen == std::string_view::npos){
                std::string_view sub_str = args_.substr(idx + 1);
                auto cnt = std::count(sub_str.begin(), sub_str.end(), ' ');
                if(cnt != whitespace_cnt - 1)
                    throw InvalidArgument("Invalid Argument: Wrong Number of Parameters");
                idx = args_.length();
            }else{
                std::string_view sub_str = args_.substr(idx + 1, next_hyphen - idx - 1);
                auto cnt = std::count(sub_str.begin(), sub_str.end(), ' ');
                if(cnt != whitespace_cnt)
                    throw InvalidArgument("Invalid Argument: Wrong Number of Parameters");
                idx = next_hyphen;
            }
            
        }
        
    }
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){
            pattern_check();
            arguments_check();
        }
    ~ArgsParser(){}

};



#endif