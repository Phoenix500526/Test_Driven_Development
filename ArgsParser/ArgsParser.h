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
            0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
            1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0
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
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){
            pattern_check();
        }
    ~ArgsParser(){}

};



#endif