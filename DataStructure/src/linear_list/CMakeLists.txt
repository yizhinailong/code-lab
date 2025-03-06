project(linear_list)

file(GLOB linear_list_sources_cpp "${linear_list_dir}/*.cpp")

add_library(${PROJECT_NAME} SHARED ${linear_list_sources_cpp})
