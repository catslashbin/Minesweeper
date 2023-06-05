#!/bin/sh

echo ">>> Prepare to build MineSweeper ..."
mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -S . -B ./build
echo ">>> Building MineSweeper ..."
cmake --build ./build --target Minesweeper --parallel $(($(nproc) - 1))
echo ">>> Success. Cd to ./build/Minesweeper and execute Minesweeper to start the game."