cmake_minimum_required(VERSION 3.15)
project(VehicleManagementSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Include header directories
include_directories(Include)

# Collect all C++ source files
file(GLOB SOURCES "Source/*.cpp")

# Define target executable
add_executable(VehicleManagSys ${SOURCES})

target_include_directories(VehicleManagSys PRIVATE Include)
