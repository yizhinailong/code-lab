project(linear_list_gtest)

set(test_cases
    linear_list_sequential_gtest
    linear_list_single_linked_gtest
)

foreach(test_case ${test_cases})
    add_executable(${test_case} ${test_case}.cpp)
    target_include_directories(${test_case} PUBLIC ${linear_list_dir})
    target_link_libraries(${test_case} PUBLIC linear_list GTest::gtest GTest::gtest_main)
    add_test(NAME ${test_case} COMMAND ${test_case})
endforeach()
