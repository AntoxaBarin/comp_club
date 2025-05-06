cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
project(comp_club)

set(TARGET_NAME "${PROJECT_NAME}")
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE 
    source/simulation.hpp
    source/simulation.cpp
    source/time.hpp
)
set(TESTS 
    test/test.cpp
)

add_executable(${TARGET_NAME} ${SOURCE} source/main.cpp)
target_compile_options(${TARGET_NAME} PUBLIC -Wall -Werror -Wextra)

add_subdirectory(googletest)
set(TEST_NAME "test_comp_club")
add_executable(${TEST_NAME} ${SOURCE} ${TESTS})
target_compile_options(${TEST_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${TEST_NAME} gtest gtest_main)
