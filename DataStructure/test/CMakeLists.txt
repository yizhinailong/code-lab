project(test_main)

enable_testing()
find_package(GTest CONFIG REQUIRED)

add_subdirectory(linear_list_gtest)
