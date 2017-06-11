set(TARGET digilo_utils_lib)
project(${TARGET})


include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

add_library(${TARGET} STATIC
        src/log.h
        src/CShmBase.h
        src/CShmBase.cpp
        src/common_utils.h
        src/file_utils.h
        src/file_utils.cpp
        src/log.cpp)

target_link_libraries(${TARGET}
        )

set(${TARGET}_LIBS
        ${TARGET}
        rt
        )

set(${TARGET}_LIBS ${${TARGET}_LIBS} PARENT_SCOPE)

set(${TARGET}_INCS
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

set(${TARGET}_INCS ${${TARGET}_INCS} PARENT_SCOPE)
