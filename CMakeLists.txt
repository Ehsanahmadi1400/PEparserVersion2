# Minimum required CMake version
cmake_minimum_required(VERSION 3.22.1)
project(MyProject)

# Add the executable
add_executable(my_executable main.cpp myfunctions.cpp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
