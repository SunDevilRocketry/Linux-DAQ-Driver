# MANUAL DEPENDENCIES
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# PROJECT
project(LinuxDriver LANGUAGES CXX)

# SOURCES
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# EXECUTABLE
add_executable(LinuxDriver ${SOURCES})

# INCLUDES
target_include_directories(LinuxDriver PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../inc"
)
