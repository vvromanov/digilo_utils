cmake_minimum_required(VERSION 2.8.7)
project(digilo_utils)


enable_language(C)
enable_language(CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
    set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

add_subdirectory(digilo_utils_lib)
add_subdirectory(gtest)
add_subdirectory(digilo_utils_test)

enable_testing()
add_test(UTILS ${PROJECT_BINARY_DIR}/digilo_utils_test/digilo_utils_test)