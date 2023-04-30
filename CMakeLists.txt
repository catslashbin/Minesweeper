cmake_minimum_required(VERSION 3.25)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

add_executable(Minesweeper-CLI
        src/core/core.c
        src/core/core.h
        src/cli.c)

add_executable(Minesweeper
        src/core/core.c
        src/core/core.h
        src/main.cpp)