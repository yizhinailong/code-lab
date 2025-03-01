cmake_minimum_required(VERSION 3.25)
project(data_structure)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(linear_list_dir ${PROJECT_SOURCE_DIR}/src/linear_list)

enable_testing()

add_subdirectory(src)
add_subdirectory(test)
