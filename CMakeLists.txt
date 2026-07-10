cmake_minimum_required(VERSION 3.10)
project(mauos_c)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Include directories
include_directories(inc)

# Source files
file(GLOB_RECURSE SOURCES "src/*.c")

# Create library
add_library(mauos_c ${SOURCES})

# Include directories for consumers
target_include_directories(mauos_c PUBLIC inc)
