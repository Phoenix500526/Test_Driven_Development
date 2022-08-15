#include <gtest/gtest.h>
#include "ArgsParser.h"
// 添加接口设计方式
using namespace std;

// Example:
//  Pattern: l:b,p:n,d:s  Args: -l -p 8080 -d /var/log

TEST(ArgsTest, should_construct_ArgsParser_Object){
     // Happy Path:
     // - TODO: construct a ArgsParser Object 
     ASSERT_NO_THROW(ArgsParser("l:b,p:n,d:s", "-l -p 8080 -d /var/log"));
}

TEST(ArgsTest, should_throw_InvalidPatternError_when_pass_a_invalid_pattern){
     GTEST_SKIP();
     // Sad Path: Invalid Pattern
     // TODO: l:bp:n,d:s
     // TODO: lb:,p:n,d:s
     // TODO: 1:b,p:n,d:s, l!b,p:n,d:s

     // Sad Path: Invalid Args
     // TODO:  "-l 123"
     // TODO: "-l -p -d /var/log"
     // TODO: "-l -p 8080 8081 -d /var/log"
}

