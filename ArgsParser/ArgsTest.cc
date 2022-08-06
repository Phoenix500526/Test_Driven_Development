#include <gtest/gtest.h>
#include <stdexcept>
#include <iostream>
#include "ArgsParser.h"
#include "TypeList.h"
// 添加接口设计方式
using namespace std;

TEST(ArgsTest, TypeListTest){
     using typelist_t = TypeList<int, double, char, string_view>;
     ASSERT_EQ(Length_v<typelist_t>, 4);
     static_assert(is_same_v<TypeAt_t<typelist_t, 0>, int>, "typelist_t[0] is not int type");
     static_assert(is_same_v<TypeAt_t<typelist_t, 1>, double>, "typelist_t[1] is not double type");
     static_assert(is_same_v<TypeAt_t<typelist_t, 2>, char>, "typelist_t[2] is not char type");
     static_assert(is_same_v<TypeAt_t<typelist_t, 3>, string_view>, "typelist_t[3] is not string_views type");
}

TEST(ArgsTest, ArgsParserConstructor) {
     // Example: -l -p 8080 -d /var/log
     // Happy Path
     auto construtor_wrapper = [](const char* pattern){
          ArgsParser<bool,int,string_view>(pattern, "-l -p 8080 -d /var/log");
     };
     ASSERT_NO_THROW(construtor_wrapper("lpd"));
     
     // Sad Path
     // TODO: 
     // 1. lpD
     // 2. lp1d
     // 3. lpld
     ASSERT_THROW(construtor_wrapper("lpD"), invalid_argument);
     ASSERT_THROW(construtor_wrapper("lp1d"), invalid_argument);
     ASSERT_THROW(construtor_wrapper("lpld"), invalid_argument);

     // Sad Path
     // TODO:
     // 1. "-l 123 -p 8080 -d /var/log"
     // 2. "-l -p -d /var/log"
     // 3. "-l -p 8080 8081 -d /var/log"
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l 123 -p 8080 -d /varlog"), invalid_argument);
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l -p 8080 8081 -d /varlog"), invalid_argument);
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l -p -d /varlog"), invalid_argument);
}
