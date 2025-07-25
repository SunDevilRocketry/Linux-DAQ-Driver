# MANUAL DEPENDENCIES
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PROJECT
project(LinuxDriver LANGUAGES CXX)

# SOURCES
set(SOURCES main.cpp)

# EXECUTABLE
add_executable(LinuxDriver ${SOURCES})
