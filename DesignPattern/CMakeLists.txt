cmake_minimum_required(VERSION 3.25)
project(DesignPattern)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(singleton_pattern)

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        message(STATUS "Using GCC, enabling ASan")
        add_compile_options(
            -fsanitize=address
            -fno-omit-frame-pointer
            -fsanitize-recover=address
        )
        add_link_options(
            -fsanitize=address
            -static-libasan
        )
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        message(STATUS "Using Clang, enabling ASan")
        add_compile_options(
            -fsanitize=address
            -fno-omit-frame-pointer
            -fsanitize-recover=address
        )
        add_link_options(
            -fsanitize=address
        )
    else()
        message(STATUS "Compiler not supported for ASan")
    endif()
else()
    message(STATUS "ASan is only supported on Linux")
endif()

find_program(CCACHE_FOUND ccache)

if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)
