#include <gtest/gtest.h>
#include <functional>
#include "ArgsParser.h"
#include "ArgsExceptions.h"
// 添加接口设计方式
using namespace std;

// Example:
//  Pattern: l:b,p:n,d:s  Args: -l -p 8080 -d /var/log

TEST(ArgsTest, should_construct_ArgsParser_Object){
     // Happy Path:
     // - TODO: construct a ArgsParser Object 
     ASSERT_NO_THROW(ArgsParser("l:b,p:n,d:s", "-l -p 8080 -d /var/log"));
}

TEST(ArgsTest, should_throw_Error_when_pass_a_invalid_pattern){
     // Sad Path: Invalid Pattern
     // TODO: l:bp:n,d:s
     auto invalid_pattern_constructor = [](const char* pattern){
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
     auto invalid_argument_constructor = [](const char* arguments){
          ArgsParser("l:b,p:n,d:s", arguments);
     };
     // TODO:  "-l 123"
     ASSERT_THROW(invalid_argument_constructor("-l 123"), InvalidArgument);
     // TODO: "-l -p -d /var/log"
     ASSERT_THROW(invalid_argument_constructor("-l -p -d /var/log"), InvalidArgument);
     // TODO: "-l -p 8080 8081 -d /var/log"
     ASSERT_THROW(invalid_argument_constructor("-l -p 8080 8081 -d /var/log"), InvalidArgument);
     // TODO: "-l -p 8080 8081 -d /var/log"
     ASSERT_THROW(invalid_argument_constructor("-l -x 8080 -d /var/log"), InvalidArgument);
}

