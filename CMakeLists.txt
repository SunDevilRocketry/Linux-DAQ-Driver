# MANUAL DEPENDENCIES
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PROJECT
project(LinuxDriver LANGUAGES CXX)

add_subdirectory(src)
add_subdirectory(inc)
add_subdirectory(example)
add_subdirectory(test)
