cmake_minimum_required(VERSION 3.9)

project(c-plus)

#include_directories(src/include)
add_subdirectory(src)

add_executable(c-plus src/main.c)
#target_link_libraries(c-plus c-plusmain)
set_property(TARGET c-plus PROPERTY C_STANDARD 99)