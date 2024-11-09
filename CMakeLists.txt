cmake_minimum_required(VERSION 3.29)
project(snail_sokoban C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "src/*.c")
add_executable(snail_sokoban.out ${SOURCES})
