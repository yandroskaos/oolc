cmake_minimum_required(VERSION 3.8.0)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/node.h
    ${CMAKE_CURRENT_SOURCE_DIR}/node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/builder.h
    ${CMAKE_CURRENT_SOURCE_DIR}/builder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/parser_nodes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/parser_nodes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/structure_nodes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/structure_nodes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/statement_nodes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/statement_nodes.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/expression_nodes.h
    ${CMAKE_CURRENT_SOURCE_DIR}/expression_nodes.cpp
    PARENT_SCOPE
)

