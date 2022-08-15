#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>
#include <cctype>
#include "ArgsExceptions.h"

class ArgsParser
{
private:
    std::string_view pattern_;
    std::string_view args_;
    
    void pattern_check(){
        size_t mask = 0b11;
        for(int idx = 0; idx < pattern_.length(); ++idx){
            if((idx & mask) == 1){
                if (pattern_[idx] != ':')
                {
                    throw InvalidPattern("Invalid Pattern: Colons error(s)");
                }
            }else if((idx & mask) == 3){
                if (pattern_[idx] != ',')
                {
                    throw InvalidPattern("Invalid Pattern: Comma error(s)");
                }
            }else{
                if(!std::islower(pattern_[idx]))
                    throw InvalidPattern("Invalid Pattern: Unsupported symbol");
            }
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