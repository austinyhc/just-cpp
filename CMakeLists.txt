cmake_minimum_required(VERSION 3.12)

project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "-g -Wall")
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)

enable_testing()

add_subdirectory(deps/abseil-cpp)
add_subdirectory(deps/benchmark)
add_subdirectory(tools)
add_subdirectory(test)
