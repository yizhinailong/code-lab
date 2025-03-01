project(linear_list_test)

add_executable(${PROJECT_NAME} linear_list_sequential_test.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${linear_list_dir})
target_link_libraries(${PROJECT_NAME} PUBLIC linear_list)

add_test(
    NAME linear_list_sequential_test
    COMMAND ${PROJECT_NAME}
)
