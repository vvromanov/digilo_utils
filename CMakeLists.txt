cmake_minimum_required(VERSION 2.8.7)
project(digilo_utils)

set(CMAKE_CXX_FLAGS "-g -Wall")


add_subdirectory(digilo_utils_lib)
add_subdirectory(gtest)
add_subdirectory(digilo_utils_test)

