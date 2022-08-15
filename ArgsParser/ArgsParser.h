#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>
#include "ArgsExceptions.h"

#include <iostream>

class ArgsParser
{
private:
    std::string_view pattern_;
    std::string_view args_;
    
    void pattern_check(){
        size_t idx = 3;
        while(idx < pattern_.length()){
            if (pattern_[idx] != ',')
            {
                throw InvalidPattern("Invalid Pattern");
            }
            idx += 4;
        }
        std::cout << std::endl;
    }
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){
            pattern_check();
        }
    ~ArgsParser(){}

};



#endif