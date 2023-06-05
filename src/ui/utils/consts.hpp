#ifndef MINESWEEPER_CONSTS_HPP
#define MINESWEEPER_CONSTS_HPP

#include <spdlog/spdlog.h>

using spdlog::debug;
using spdlog::info;
using spdlog::warn;

/* clang-format off */

#define DP *8
#define ARCDP /8
#define DEF_WIN_WIDTH 120 DP
#define DEF_WIN_HEIGHT 120 DP

#define ASSETS_DIR "../src/ui/assets/"
#define TITLE_BG_COLOR sf::Color{ 0xF1FAFEFF }
#define NOT_CLICKED_COLOR sf::Color{ 0xE5F7FFFF }
#define HOVER_COLOR sf::Color { 0x00a4bdbf }
#define TITLE_COLOR sf::Color{ 0x00547AFF }
#define SECONDARY_COLOR sf::Color{ 0x699EB5FF }
#define TITLE_Y 3.5 DP

/* clang-format on */

#endif //MINESWEEPER_CONSTS_HPP
