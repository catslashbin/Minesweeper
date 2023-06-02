#ifndef MINESWEEPER_CONSTS_HPP
#define MINESWEEPER_CONSTS_HPP

#include <spdlog/spdlog.h>

using spdlog::info;
using spdlog::warn;
using spdlog::debug;

/* clang-format off */

#define DP *8
#define ARCDP /8
#define WIN_WIDTH 120 DP
#define WIN_HEIGHT 120 DP
#define WIN_TITLE L"Material 3 扫雷"

#define ASSETS_DIR "../src/ui/assets/"
#define TITLE_BG_COLOR sf::Color{ 0xF6FCFFFF }
#define TITLE_COLOR sf::Color{ 0x00547AFF }
#define TITLE_Y 3.5 DP

/* clang-format on */

#endif //MINESWEEPER_CONSTS_HPP
