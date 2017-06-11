cmake_minimum_required(VERSION 2.8.7)
set(TARGET gtest)
project(${TARGET})

set(${TARGET}_SRCS
    src/gtest-all.cc
    src/gtest/gtest.h
    src/gtest_main.cc
)

set_source_files_properties(src/gtest-all.cc PROPERTIES COMPILE_FLAGS "-Wno-missing-declarations")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(${TARGET} STATIC
    ${${TARGET}_SRCS}
)

#target_link_libraries(${TARGET}
#        minizip
#        z
#)

set(${TARGET}_LIBS
	${TARGET}
)

set(${TARGET}_LIBS ${${TARGET}_LIBS} PARENT_SCOPE)

set(${TARGET}_INCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
set(${TARGET}_INCS ${${TARGET}_INCS} PARENT_SCOPE)
