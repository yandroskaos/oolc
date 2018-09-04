cmake_minimum_required(VERSION 3.8.0)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/tokens.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scanner.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp    
    ${CMAKE_CURRENT_SOURCE_DIR}/parser.h
    ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/check_syntax_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/check_syntax_visitor.cpp
    PARENT_SCOPE
)

