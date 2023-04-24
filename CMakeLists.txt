cmake_minimum_required(VERSION 3.24)
project(snake_in_c C)

set(CMAKE_C_STANDARD 11)

# Set the location of the library files
set(CANVAS_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Add the canvas library
add_library(canvas SHARED IMPORTED)
set_target_properties(canvas PROPERTIES IMPORTED_LOCATION ${CANVAS_LIB_PATH}/canvas.dll)
set_target_properties(canvas PROPERTIES IMPORTED_IMPLIB ${CANVAS_LIB_PATH}/canvas.lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add the executable and link it with the canvas library
add_executable(snake_in_c main.c)
target_link_libraries(snake_in_c canvas)
