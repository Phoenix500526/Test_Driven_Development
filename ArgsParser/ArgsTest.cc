#include <gtest/gtest.h>
#include "ArgsParser.h"
// 添加接口设计方式
TEST(ArgsTest, should) {
     // Example: -l -p 8080 -d /var/log
     ArgsParser args{"l:b,p:i,d:s", "-l -p 8080 -d /var/log"};
     EXPECT_EQ(args.get_idx('l'), 0);
}
