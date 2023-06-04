#ifndef MINESWEEPER_MINE_FIELD_HPP
#define MINESWEEPER_MINE_FIELD_HPP


#include "core/core.hpp"
#include "mine_cell.hpp"
#include <vector>

#define MARGIN_BY_SIDE_RADIO 0.3

class MineField {
private:
    GameCore game_core_;
    std::vector<MineCell> cells_;
    float cell_side_length_;
    int field_length_;
    int field_height_;
    int num_mines_;
    sf::Vector2f position_;

public:
    MineField(int field_length, int field_height, int num_mines, sf::Vector2f position, float cell_side_length);

    void update(sf::RenderWindow &window);

    void setupUI();
};


#endif //MINESWEEPER_MINE_FIELD_HPP
