add_executable(ArgsTest ArgsTest.cc)
target_link_libraries(ArgsTest GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(ArgsTest)
add_test(NAME ArgsTest COMMAND ArgsTest)