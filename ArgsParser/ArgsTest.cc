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
     static_assert(std::is_same_v<TypeAt_t<typelist_t, 0>, int>, "typelist_t[0] is not int type");
     static_assert(std::is_same_v<TypeAt_t<typelist_t, 1>, double>, "typelist_t[1] is not double type");
     static_assert(std::is_same_v<TypeAt_t<typelist_t, 2>, char>, "typelist_t[2] is not char type");
     static_assert(std::is_same_v<TypeAt_t<typelist_t, 3>, string_view>, "typelist_t[3] is not string_views type");
}

TEST(ArgsTest, GetIndexFromPattern) {
     GTEST_SKIP() << "Skipping single test";
     // Example: -l -p 8080 -d /var/log
     // Happy Path
     ArgsParser<bool,int,const char *> args{"llpd", "-l -p 8080 -d /var/log"};
     // EXPECT_EQ(args.get_idx('l'), 0);
     // EXPECT_EQ(args.get_idx('p'), 1);
     // EXPECT_EQ(args.get_idx('d'), 2);
     // EXPECT_EQ(args.get_idx('f'), -1);
     // Sad Path
     // TODO: 
     // 1. l:bp:i,d:s
     // 2. :lb,p:i,d:s
     // 3. lb:,p:i,
     // ASSERT_THROW(ArgsParser<bool,int,const char *>("lpD", "-l -p 8080 -d /varlog"), invalid_argument);
     // ASSERT_THROW(ArgsParser<bool,int,const char *>("lp1d", "-l -p 8080 -d /varlog"), invalid_argument) << __LINE__ << '\n';

     // Sad Path
     // TODO:
     // 1. "-l 123 -p 8080 -d /var/log"
     // 2. "-l -p -d /var/log"
     // 3. "-l -p 8080 8081 -d /var/log"
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l 123 -p 8080 -d /varlog"), invalid_argument);
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l -p 8080 8081 -d /varlog"), invalid_argument);
     // ASSERT_THROW(ArgsParser("l:b,p:i,d:s", "-l -p -d /varlog"), invalid_argument);
}
