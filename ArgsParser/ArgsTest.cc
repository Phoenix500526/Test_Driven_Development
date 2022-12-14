#include <gtest/gtest.h>

#include <functional>

#include "ArgsExceptions.h"
#include "ArgsParser.h"
// 添加接口设计方式
using namespace std;

// Example:
//  Pattern: l:b,p:n,d:s  Args: -l -p 8080 -d /var/log

TEST(ArgsTest, should_construct_ArgsParser_Object) {
    // Happy Path:
    // - TODO: construct a ArgsParser Object
    ASSERT_NO_THROW(ArgsParser("l:b,p:n,d:s", "-l -p 8080 -d /var/log"));
}

TEST(ArgsTest, should_throw_Error_when_pass_a_invalid_pattern) {
    // Sad Path: Invalid Pattern
    // TODO: l:bp:n,d:s
    auto invalid_pattern_constructor = [](const char* pattern) {
        ArgsParser(pattern, "-l -p 8080 -d /var/log");
    };
    ASSERT_THROW(invalid_pattern_constructor("l:bp:n,d:s"), InvalidPattern);
    // TODO: lb:,p:n,d:s
    ASSERT_THROW(invalid_pattern_constructor("lb:,p:n,d:s"), InvalidPattern);
    // TODO: 1:b,p:n,d:s, l!b,p:n,d:s
    ASSERT_THROW(invalid_pattern_constructor("1:b,p:n,d:s"), InvalidPattern);
    ASSERT_THROW(invalid_pattern_constructor("l!b,p:n,d:s"), InvalidPattern);
    // TODO: l:x,p:n,d:s
    ASSERT_THROW(invalid_pattern_constructor("l:x,p:n,d:s"), InvalidPattern);

    // Sad Path: Invalid Args
    auto invalid_argument_constructor = [](const char* arguments) {
        ArgsParser("l:b,p:n,d:s", arguments);
    };
    // TODO:  "-l 123"
    ASSERT_THROW(invalid_argument_constructor("-l 123"), InvalidArgument);
    // TODO: "-l -p -d /var/log"
    ASSERT_THROW(invalid_argument_constructor("-l -p -d /var/log"),
                 InvalidArgument);
    // TODO: "-l -p 8080 8081 -d /var/log"
    ASSERT_THROW(invalid_argument_constructor("-l -p 8080 8081 -d /var/log"),
                 InvalidArgument);
    // TODO: "-l -p 8080 8081 -d /var/log"
    ASSERT_THROW(invalid_argument_constructor("-l -x 8080 -d /var/log"),
                 InvalidArgument);
}

TEST(ArgsTest, should_get_a_relevant_value_by_the_give_option) {
    // TODO: getBool('l')
    ArgsParser parser{"l:b,p:n,d:s", "-l -p 8090 -d /var/log"};
    ASSERT_TRUE(parser.getBoolean('l'));
    // TODO: getNumber('p')
    ASSERT_EQ(parser.getNumber('p'), 8090);
    // TODO: getString('d')
    ASSERT_EQ(parser.getString('d'), string_view{"/var/log"});

    // TODO: get_default value of -l and -d —— "-p 8081"
    ArgsParser parser_1{"l:b,p:n,d:s", "-p 8081"};
    ASSERT_FALSE(parser_1.getBoolean('l'));
    ASSERT_EQ(parser_1.getString('d'), string_view{""});
    ASSERT_EQ(parser_1.getNumber('p'), 8081);

    // TODO: get_default value of -p and -d —— "-l"
    ArgsParser parser_2{"l:b,p:n,d:s", "-l"};
    ASSERT_TRUE(parser_2.getBoolean('l'));
    ASSERT_EQ(parser_2.getString('d'), string_view{""});
    ASSERT_EQ(parser_2.getNumber('p'), 8000);

    // TODO: get_default value of -l and -p —— "-d /var/log"
    ArgsParser parser_3{"l:b,p:n,d:s", "-d /var/log"};
    ASSERT_FALSE(parser_3.getBoolean('l'));
    ASSERT_EQ(parser_3.getString('d'), string_view{"/var/log"});
    ASSERT_EQ(parser_3.getNumber('p'), 8000);

    // TODO: get_default value of -l , -d and -p —— ""
    ArgsParser parser_4{"l:b,p:n,d:s", ""};
    ASSERT_FALSE(parser_4.getBoolean('l'));
    ASSERT_EQ(parser_4.getString('d'), string_view{""});
    ASSERT_EQ(parser_4.getNumber('p'), 8000);
}
