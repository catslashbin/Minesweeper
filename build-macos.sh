#!/bin/zsh

echo ">>> Prepare to build MineSweeper ..."
mkdir -p build
cmake -DCMAKE_OSX_ARCHITECTURES:STRING=x86_64 -Dfmt_DIR:PATH=/usr/local/homebrew/lib/cmake/fmt -Dspdlog_DIR:PATH=/usr/local/homebrew/lib/cmake/spdlog -DCMAKE_BUILD_TYPE=Release -S . -B ./build
echo ">>> Building MineSweeper ..."
cmake --build ./build --target Minesweeper --parallel $(($(nproc) - 1))
echo ">>> Success. Cd to ./build/Minesweeper and execute Minesweeper to start the game."