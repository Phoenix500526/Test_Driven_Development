#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>
#include <stdexcept>
#include <algorithm>
#include <iostream>
class ArgsParser
{
private:
    std::string_view pattern_;
    std::string_view args_;
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){
            size_t cnt_of_comma = std::count(pattern_.begin(), pattern_.end(), ',');
            size_t cnt_of_colon = std::count(pattern_.begin(), pattern_.end(), ':');
            if(cnt_of_comma != cnt_of_colon - 1){
                throw std::invalid_argument("Invalid Pattern: ");
            }
            size_t start = 0, end = pattern_.find(',');
            while(end != std::string_view::npos){
                size_t len = end - start;
                std::string_view temp = pattern_.substr(start, len);
                size_t colon_pos = temp.find(':');
                if(colon_pos == std::string_view::npos || colon_pos == 0 || colon_pos == temp.size() - 1)
                    throw std::invalid_argument("Invalid Pattern: ");
                start = end + 1;
                end = pattern_.find(',', start);
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