cmake_minimum_required(VERSION 3.12)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")

# set_target_property()

file(GLOB LEETLIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_executable(leetcli
    tools/leetcli.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/cxxopts/cxxopts.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/httplib/httplib.h
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/nlohmann/json.hpp)

target_include_directories(leetcli SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/deps)


enable_testing()

find_package(GTest REQUIRED)

add_executable(
    leet_test
    ${CMAKE_CURRENT_SOURCE_DIR}/test/0001_two_sum_test.cc)

# add_subdirectory(GTest)

target_include_directories(leet_test SYSTEM PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/utils)

target_link_libraries(leet_test GTest::gtest_main)
add_test(NAME that-test-I-made COMMAND leet_test)
