#ifndef ARGS_EXCEPTIONS_H
#define ARGS_EXCEPTIONS_H
#include <stdexcept>

class InvalidPattern : public std::invalid_argument{
public:
    InvalidPattern(const char* what_args) : std::invalid_argument(what_args){}
};

class InvalidArgument : public std::invalid_argument{
public:
    InvalidArgument(const char* what_args) : std::invalid_argument(what_args){}
};

#endif