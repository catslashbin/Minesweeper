cmake_minimum_required(VERSION 3.25)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

include_directories(src)

add_executable(Minesweeper-CLI
        src/core/core.c
        src/core/core.h
        src/cli.c)

add_executable(Minesweeper-test
        src/core/core.c
        src/core/core.h
        src/test.c)

add_executable(
        Minesweeper
        src/core/core.c
        src/core/core.h
        src/main.cpp
        src/ui/scene.hpp
        src/ui/scene.cpp
        src/ui/game.hpp
        src/ui/game.cpp
        src/ui/consts.hpp
        src/ui/scenes/menu_scene.hpp
        src/ui/scenes/menu_scene.cpp
        src/ui/scenes/field_scene.cpp
        src/ui/scenes/field_scene.hpp
        src/core/core.hpp
        src/ui/button.cpp
        src/ui/button.hpp
        src/ui/res_pool.cpp
        src/ui/res_pool.hpp)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(spdlog REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

target_link_libraries(Minesweeper PRIVATE sfml-graphics sfml-audio sfml-window sfml-system spdlog::spdlog)