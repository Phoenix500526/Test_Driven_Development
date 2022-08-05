#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <string_view>

class ArgsParser
{
private:
    std::string_view pattern_;
    std::string_view args_;
    
public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args){}
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