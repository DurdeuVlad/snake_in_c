cmake_minimum_required(VERSION 3.20)
project(test_use_library_in_c)

set(CMAKE_C_STANDARD 11)

add_executable(test_use_library_in_c main.c snake_methods.c)
add_library(snake_methods_library snake_methods.h snake_methods.c)