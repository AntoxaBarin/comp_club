cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
project(comp_club)

set(TARGET_NAME "${PROJECT_NAME}")
set(PROJECT_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE 
    source/main.cpp
    source/simulation.hpp
    source/simulation.cpp
    source/time.hpp
)

add_executable(${TARGET_NAME} ${SOURCE})
target_compile_options(${TARGET_NAME} PUBLIC -Wall -Werror -Wextra)
