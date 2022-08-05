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
        return std::string_view::npos;
    }
};



#endif