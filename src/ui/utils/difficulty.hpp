//
// Created by Tianze Ds on 2023/6/3.
//

#include "consts.hpp"

#ifndef MINESWEEPER_DIFFICULTY_HPP
#define MINESWEEPER_DIFFICULTY_HPP

class Difficulty {

public:
    enum Level {
        Easy,
        Medium,
        Hard,
        Custom
    };

    constexpr static int MineData[4][3] = {{9, 9, 10},
                                           {16, 16, 40},
                                           {16, 30, 99},
                                           {-1, -1, -1}};

    constexpr static float WindowSize[4][2] = {{DEF_WIN_WIDTH, DEF_WIN_HEIGHT},
                                               {DEF_WIN_WIDTH, DEF_WIN_HEIGHT},
                                               {1.7 * DEF_WIN_WIDTH, DEF_WIN_HEIGHT},
                                               {-1, -1}};
};

#endif //MINESWEEPER_DIFFICULTY_HPP
