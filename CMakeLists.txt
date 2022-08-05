cmake_minimum_required(VERSION 3.13)
project(Test_Driven_Development)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.91chi.fun/https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)
set(CMAKE_CTEST_ARGUMENTS "--verbose")

enable_testing()

find_file(CLANG_FORMAT_BIN_NAME clang-format) 
if(CLANG_FORMAT_BIN_NAME)
    message(STATUS "Code Formatter:  ${CLANG_FORMAT_BIN_NAME}")
    file(GLOB_RECURSE ALL_SOURCE_FILES *.h *.cc)
    add_custom_target(
            format
            COMMAND ${CLANG_FORMAT_BIN_NAME}
            -i
            ${ALL_SOURCE_FILES}
    )
endif()

add_subdirectory(ArgsParser)