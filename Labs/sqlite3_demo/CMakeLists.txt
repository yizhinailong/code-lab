cmake_minimum_required(VERSION 3.30)
project(sqlite3_demo)

macro(create_executable NAME)
    add_executable(${NAME} ${NAME}.cpp)
    target_link_libraries(${NAME} PRIVATE SQLiteCpp)
endmacro(create_executable)

find_package(SQLiteCpp CONFIG REQUIRED)

create_executable(demo_1)
create_executable(demo_2)
