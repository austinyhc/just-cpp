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

file(GLOB tests ${CMAKE_CURRENT_SOURCE_DIR}/test/*.cc)

add_subdirectory(deps/abseil-cpp)

foreach(test ${tests})

    string(REGEX REPLACE "_test.cc" ".h" output ${test})
    string(REGEX REPLACE "/test/" "/src/" output ${output})

    get_filename_component(test_command ${test} NAME_WE)
    get_filename_component(test_name ${output} NAME_WE)

    add_executable(${test_command} ${test})

    target_include_directories(${test_command} SYSTEM PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/include)

    target_link_libraries(${test_command} absl::base absl::synchronization absl::strings)

    target_link_libraries(${test_command} GTest::gtest_main)
    add_test(NAME ${test_name} COMMAND ${test_command})
endforeach()

