cmake_minimum_required(VERSION 3.11)

project(oolc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(BISON)
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/tokens.h
    COMMAND ${BISON_EXECUTABLE} --defines=${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/tokens.h -l -o ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/parser.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/parser.y
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/parser.y)
add_custom_target(parser ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/parser.y)

find_package(FLEX)
add_custom_command(
    OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/scanner.cpp
    COMMAND ${FLEX_EXECUTABLE} -L -w -o ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/scanner.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/scanner.l
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/scanner.l)
add_custom_target(scanner ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/scanner.l ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/parser.y)

include_directories(src)

add_subdirectory(src)
              
add_executable(oolc ${SOURCES})
