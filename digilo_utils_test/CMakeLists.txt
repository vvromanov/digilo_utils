set(TARGET digilo_utils_test)

project(${TARGET})

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${digilo_utils_lib_INCS}
        ${gtest_INCS}
)

add_executable(${TARGET}
        src/CShmBase_Test.cpp
        src/FileUtils_Test.cpp
        )

target_link_libraries(${TARGET}
        ${gtest_LIBS}
        ${digilo_utils_lib_LIBS}
        pthread
        )

