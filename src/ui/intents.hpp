#ifndef MINESWEEPER_INTENTS_HPP
#define MINESWEEPER_INTENTS_HPP

#include <cstdio>

enum GameScene {
    MENU = 0,
    GAMING = 1,
    CUSTOMIZE_FIELD = 2
};

struct Intent {
    GameScene target_intent;
};

struct StartGameIntent : Intent {
    size_t field_width;
    size_t field_height;
    size_t num_mines;
};


#endif //MINESWEEPER_INTENTS_HPP
