#include <gtest/gtest.h>
#include <stdexcept>
#include <functional>
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
     auto construtor_wrapper = [](const char* pattern, const char* args){
          ArgsParser<bool,int,string_view>(pattern, args);
     };

     // Happy Path
     auto pattern_checker = bind(construtor_wrapper, placeholders::_1, "-l -p 8080 -d /var/log");
     ASSERT_NO_THROW(pattern_checker("lpd"));
     
     // Sad Path
     // TODO: 
     // 1. lpD
     // 2. lp1d
     // 3. lpld
     ASSERT_THROW(pattern_checker("lpD"), invalid_argument);
     ASSERT_THROW(pattern_checker("lp1d"), invalid_argument);
     ASSERT_THROW(pattern_checker("lpld"), invalid_argument);

     // Sad Path
     // TODO:
     // 1. "-l 123"
     // 2. "-l -p -d /var/log"
     // 3. "-l -p 8080 8081 -d /var/log"
     auto arguments_checker = bind(construtor_wrapper, "lpd", placeholders::_1);
     ASSERT_THROW(arguments_checker("-l 123"), invalid_argument);
     
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l -p 8080 8081 -d /varlog"), invalid_argument);
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l -p -d /varlog"), invalid_argument);
}
