cmake_minimum_required(VERSION 3.17)
project(undividual_task_2)

set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage -Werror -Wpedantic")
set(CMAKE_C_FLAGS "-g -O0 -Wall -W -fprofile-arcs -ftest-coverage -Werror -Wpedantic")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -pthread")

option(IS_STATIC ON)

add_library(file_generator STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/file_generator/sources/file_generator.c)
target_include_directories(file_generator PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/file_generator/include)

add_library(neutral_functions STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/neutral_functions/sources/neutral_functions.c)
target_include_directories(neutral_functions PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/neutral_functions/include)

add_library(_static STATIC single/single.c)
target_include_directories(_static PUBLIC ${PROJECT_SOURCE_DIR}/neutral_functions)
target_link_libraries(_static neutral_functions)

add_library(_dynamic SHARED parallel/parallel.c)
target_include_directories(_dynamic PUBLIC
        ${PROJECT_SOURCE_DIR}/neutral_functions)
target_link_libraries(_dynamic PUBLIC neutral_functions m)

add_executable(main main.c)
target_include_directories(main PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/single/include
        ${CMAKE_CURRENT_SOURCE_DIR}/file_generator)

if(IS_STATIC)
    target_link_libraries(main file_generator _static)
else()
    target_link_libraries(main file_generator _dynamic)
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
enable_testing()

add_executable(tests_static tests/test_static.cpp)

target_include_directories(tests_static PUBLIC
        ${PROJECT_SOURCE_DIR}/neutral_functions)

target_link_libraries(tests_static gtest_main _static)

add_executable(tests_dynamic tests/test_dynamic.cpp)


target_include_directories(tests_dynamic PUBLIC
        ${PROJECT_SOURCE_DIR}/neutral_functions)

target_link_libraries(tests_dynamic gtest_main _dynamic)

