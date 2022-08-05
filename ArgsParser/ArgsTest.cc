#include <gtest/gtest.h>
#include "ArgsParser.h"
// 添加接口设计方式
TEST(ArgsTest, GetIndexFromPattern) {
     // Example: -l -p 8080 -d /var/log
     // Happy Path
     ArgsParser args{"l:b,p:i,d:s", "-l -p 8080 -d /var/log"};
     EXPECT_EQ(args.get_idx('l'), 0);
     EXPECT_EQ(args.get_idx('p'), 1);
     EXPECT_EQ(args.get_idx('d'), 2);
     EXPECT_EQ(args.get_idx('f'), -1);
}
