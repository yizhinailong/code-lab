cmake_minimum_required(VERSION 3.25)
project(data_structure)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(linear_list_dir ${PROJECT_SOURCE_DIR}/src/linear_list)

find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    add_compile_options(
        -fsanitize=address
        -fno-omit-frame-pointer
        -fsanitize-recover=address
    )

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        message(STATUS "Using GCC, enabling ASan")
        add_link_options(
            -fsanitize=address
            -static-libasan
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(STATUS "Using Clang, enabling ASan")
        add_link_options(
            -fsanitize=address
        )
    endif()
endif()

add_subdirectory(src)
add_subdirectory(test)
