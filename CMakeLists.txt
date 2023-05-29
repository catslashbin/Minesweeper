cmake_minimum_required(VERSION 3.25)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

include_directories(src)

add_executable(Minesweeper-CLI
        src/core/core.c
        src/core/core.h
        src/cli.c)

add_executable(Minesweeper-test
        src/core/core.c
        src/core/core.h
        src/test.c)

add_executable(Minesweeper
        src/core/core.c
        src/core/core.h
        src/main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(Minesweeper PRIVATE sfml-graphics sfml-audio sfml-window sfml-system)