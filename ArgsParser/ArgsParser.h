#ifndef TDD_ARGPARSER_H
#define TDD_ARGPARSER_H
#include <cctype>
#include <charconv>
#include <functional>
#include <iostream>
#include <string_view>
#include <tuple>
#include <unordered_map>

#include "ArgsExceptions.h"
class ArgsParser {
private:
    std::string_view pattern_;
    std::string_view args_;
    std::unordered_map<char, std::any> table_;
    inline static char whitespaces_[26] = {0, 1, 0, 0, 0, 0, 0, 0, 0,
                                           0, 0, 0, 0, 2, 0, 0, 0, 0,
                                           2, 0, 0, 0, 0, 0, 0, 0};
    std::function<void(const char, const std::string_view)>
        parameter_generator_[26];
    std::function<void(const size_t)> predicator_[4];

    inline void init_pattern_checker() {
        predicator_[0] = [this](const size_t idx) {
            if (!std::islower(pattern_[idx]))
                throw InvalidPattern("Invalid Pattern: Invalid Option");
        };
        predicator_[1] = [this](const size_t idx) {
            if (pattern_[idx] != ':')
                throw InvalidPattern("Invalid Pattern: Colons Error");
        };
        predicator_[2] = [this](const size_t idx) {
            if (!std::islower(pattern_[idx]) ||
                !whitespaces_[pattern_[idx] - 'a'])
                throw InvalidPattern(
                    "Invalid Pattern: Unsupproted Option Type");
        };
        predicator_[3] = [this](const size_t idx) {
            if (pattern_[idx] != ',')
                throw InvalidPattern("Invalid Pattern: Commas Error");
        };
    }

    inline void init_parameter_generator() {
        parameter_generator_['b' - 'a'] = [this](const char opt,
                                                 const std::string_view) {
            this->table_[opt] = std::make_any<bool>(true);
        };

        parameter_generator_['n' - 'a'] =
            [this](const char opt, const std::string_view value_str) {
                int32_t value;
                if (std::from_chars(value_str.begin(), value_str.end(), value)
                        .ec != std::errc{}) {
                    throw InvalidArgument(
                        "Invalid Argument: Unmatch type and argument");
                }
                this->table_[opt] = std::make_any<int32_t>(value);
            };

        parameter_generator_['s' - 'a'] =
            [this](const char opt, const std::string_view value_str) {
                this->table_[opt] = std::make_any<std::string_view>(value_str);
            };
    }

    void init() {
        init_pattern_checker();
        init_parameter_generator();
    }

    void pattern_check() {
        size_t mask = 0b11;
        for (int idx = 0; idx < pattern_.length(); ++idx) {
            predicator_[idx & mask](idx);
        }
    }

    inline std::string_view get_option_and_parameter(std::string_view str) {
        auto parameter = str.substr(2);
        auto last_whitespace = parameter.find_last_of(' ');
        if (last_whitespace != std::string_view::npos) {
            parameter.remove_suffix(parameter.size() - last_whitespace);
        }
        return parameter;
    };

    void check_whitespace(const size_t start, const size_t end) {
        size_t idx = pattern_.find(args_[start]);
        if (idx == std::string_view::npos)
            throw InvalidArgument("Invalid Argument: Undefined  Argument");
        size_t type_idx = idx + 2;
        size_t length = end != std::string_view::npos ? end - start : end;
        size_t whitespace_cnt =
            end != std::string_view::npos
                ? whitespaces_[pattern_[type_idx] - 'a']
                : whitespaces_[pattern_[type_idx] - 'a'] - 1;

        std::string_view sub_str = args_.substr(start, length);

        auto cnt = std::count(sub_str.begin(), sub_str.end(), ' ');
        if (cnt != whitespace_cnt)
            throw InvalidArgument(
                "Invalid Argument: Wrong Number of Parameters");

        auto value_str = get_option_and_parameter(sub_str);
        parameter_generator_[pattern_[type_idx] - 'a'](args_[start], value_str);
    }

    void arguments_check() {
        size_t idx = 0;
        while (idx != std::string_view::npos) {
            size_t next_hyphen = args_.find('-', idx + 1);
            check_whitespace(idx + 1, next_hyphen);
            idx = next_hyphen;
        }
    }

public:
    ArgsParser(const char* pattern, const char* args)
        : pattern_(pattern), args_(args) {
        init();
        pattern_check();
        arguments_check();
    }
    ~ArgsParser() {}

    bool getBoolean(const char option) {
        return table_.find(option) != table_.end() ? true : false;
    }

    int32_t getNumber(const char option) {
        if (table_.find(option) != table_.end()) {
            return std::any_cast<int32_t>(table_[option]);
        }
        return 8080;
    }

    std::string_view getString(const char option) {
        using namespace std::literals;
        if (table_.find(option) != table_.end())
            return std::any_cast<std::string_view>(table_[option]);
        return ""sv;
    }
};

#endif