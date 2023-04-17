# add_executable(leetcli main.cc)
# target_link_libraries(leetcli
#     libcxxopts
#     libhttplib
#     libjson
# )

add_executable(leetcli
    leetcli.cpp
    ${PROJECT_SOURCE_DIR}/deps/cxxopts/cxxopts.hpp
    ${PROJECT_SOURCE_DIR}/deps/httplib/httplib.h
    ${PROJECT_SOURCE_DIR}/deps/nlohmann/json.hpp)

target_include_directories(leetcli SYSTEM PRIVATE ${PROJECT_SOURCE_DIR}/deps)

install(TARGETS leetcli DESTINATION bin)
