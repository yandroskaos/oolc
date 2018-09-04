cmake_minimum_required(VERSION 3.8.0)

add_subdirectory(ast)
add_subdirectory(code_generation)
add_subdirectory(errors)
add_subdirectory(parsing)
add_subdirectory(semantics)
add_subdirectory(symbols)
add_subdirectory(types)
add_subdirectory(utils)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/compiler.h
    PARENT_SCOPE
)

