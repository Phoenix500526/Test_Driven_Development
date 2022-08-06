#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <any>
#include <unordered_map>
#include "TypeList.h"





template <typename... Args>
class ArgsParser
{
private:
    using TypeList_t = TypeList<Args...>;
    std::string_view pattern_;
    std::string_view args_;
    std::unordered_map<char, std::any> table_;
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){
            bool charset[26] = {false};
            for(const char c : pattern_){
                if(!std::islower(c) && charset[c - 'a'])
                    throw std::invalid_argument("Invalid Pattern");
                charset[c - 'a'] = true;
            }
        }
    ~ArgsParser(){}

    constexpr size_t get_idx(const char c){
        if(pattern_[0] == c)
            return 0;

        size_t pos = pattern_.find(','), idx = 1;

        while( pos != std::string_view::npos){
            if(pattern_[pos + 1] == c){
                return idx;
            }
            ++idx;
            pos = pattern_.find(',', pos + 1);
        }
        return -1;
    }
};



#endif