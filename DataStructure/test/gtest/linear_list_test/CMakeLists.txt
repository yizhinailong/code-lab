project(linear_list_gtest)

add_executable(${PROJECT_NAME} linear_list_sequential_gtest.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${linear_list_dir})
target_link_libraries(${PROJECT_NAME} PUBLIC linear_list GTest::gtest GTest::gtest_main)

add_test(
    NAME linear_list_sequential_gtest
    COMMAND ${PROJECT_NAME}
)
