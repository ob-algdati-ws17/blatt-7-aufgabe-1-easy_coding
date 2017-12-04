cmake_minimum_required(VERSION 3.8)
project(AVLTree)

set(CMAKE_CXX_STANDARD 11)

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

set(SOURCE_FILES avltree/main.cpp)
add_executable(AVLTree ${SOURCE_FILES})