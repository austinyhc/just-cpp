file(GLOB tests ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

foreach(test ${tests})

    string(REGEX REPLACE "_test.cc" ".h" output ${test})
    string(REGEX REPLACE "/test/" "/solution/" output ${output})

    get_filename_component(test_command ${test} NAME_WE)
    get_filename_component(test_name ${output} NAME_WE)

    add_executable(${test_command} ${test})

    target_include_directories(${test_command} SYSTEM PUBLIC
        ${PROJECT_SOURCE_DIR}/deps
        ${PROJECT_SOURCE_DIR}/solution
        ${PROJECT_SOURCE_DIR}/include)

    target_link_libraries(${test_command}
        absl::base
        absl::synchronization absl::strings
        GTest::gtest_main
        benchmark::benchmark)

    target_link_libraries(${test_command} GTest::gtest_main)
    add_test(NAME ${test_name} COMMAND ${test_command})

endforeach()
