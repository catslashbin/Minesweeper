#ifndef MINESWEEPER_CONSTS_HPP
#define MINESWEEPER_CONSTS_HPP

#include <spdlog/spdlog.h>

using spdlog::debug;
using spdlog::info;
using spdlog::warn;

/* clang-format off */

#define DP *8
#define DP_INV /(1 DP)

#define DEF_WIN_WIDTH 120 DP
#define DEF_WIN_HEIGHT 120 DP

#define ASSETS_DIR "../src/ui/assets/"

#define COLOR_TITLE_BG sf::Color{ 0xF1FAFEFF }
#define COLOR_NOT_CLICKED sf::Color{ 0xE5F7FFFF }
#define COLOR_HOVER sf::Color { 0x0E74A19F }
#define COLOR_TITLE sf::Color{ 0x00547AFF }
#define COLOR_SECONDARY sf::Color{ 0x699EB5FF }
#define COLOR_MINE sf::Color{ 0xCD4B4BFF }
#define COLOR_WIN sf::Color{ 0x30AC6FFF }

#define TITLE_Y 3.5 DP

#define EPS_DOUBLE_CLICK 300

#define DEBUG_ENABLE_CHEAT false

/* clang-format on */

#endif //MINESWEEPER_CONSTS_HPP
