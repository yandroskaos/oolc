cmake_minimum_required(VERSION 3.8.0)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/beautifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/beautifier.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/method_variables_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/method_variables_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/il_generator.h
    ${CMAKE_CURRENT_SOURCE_DIR}/il_generator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/code_generation.h
    ${CMAKE_CURRENT_SOURCE_DIR}/code_generation.cpp
    PARENT_SCOPE
)

