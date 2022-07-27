cmake_minimum_required(VERSION 3.13)
project(ArgParser)

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