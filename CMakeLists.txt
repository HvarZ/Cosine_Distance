cmake_minimum_required(VERSION 3.17)
project(undividual_task_2 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -Werror -Wpedantic")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage -Werror -Wpedantic")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")

add_library(distance STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/single/sources/cos_distance.c)
target_include_directories(distance PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/single/include)

add_executable(main
        main.c)
target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/single/include)
target_link_libraries(main distance)