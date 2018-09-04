cmake_minimum_required(VERSION 3.8.0)

set(SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/main_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/interface_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/interface_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/return_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/return_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types_builder_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types_builder_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/types_decorator_visitor.h
    ${CMAKE_CURRENT_SOURCE_DIR}/types_decorator_visitor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/semantics.h
    ${CMAKE_CURRENT_SOURCE_DIR}/semantics.cpp
    PARENT_SCOPE
)

