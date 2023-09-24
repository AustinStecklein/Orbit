cmake_minimum_required(VERSION 3.17)

add_executable(scr
    Orbit.cpp)

add_library (src Orbit.cpp)
target_include_directories (src PUBLIC )