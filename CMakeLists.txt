cmake_minimum_required(VERSION 3.10)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 17)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

include_directories(src)

file(GLOB_RECURSE CORE CONFIGURE_DEPENDS "src/core/*.cpp" "src/core/*.c")
file(GLOB_RECURSE UI CONFIGURE_DEPENDS "src/ui/*.cpp")
file(GLOB_RECURSE TEST CONFIGURE_DEPENDS "test/*.cpp")

message("-- ProjectSourceDir: ${PROJECT_SOURCE_DIR}")
message("-- GLOB: \${CORE}: ${CORE}")
message("-- GLOB: \${UI}: ${UI}")
message("-- GLOB: \${TEST}: ${TEST}")

add_executable(Minesweeper-CLI ${CORE} src/cli.c)
add_executable(Minesweeper-CLI-Test ${CORE} src/test.c)
add_executable(Minesweeper ${CORE} ${UI} src/main.cpp)
add_executable(Minesweeper-Test ${CORE} ${UI} ${TEST} test/test_main.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics audio REQUIRED)
find_package(spdlog REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(Minesweeper PRIVATE sfml-graphics sfml-audio sfml-window sfml-system spdlog::spdlog)
target_link_libraries(Minesweeper-Test PRIVATE sfml-graphics sfml-audio sfml-window sfml-system spdlog::spdlog)
