#ifndef MINESWEEPER_MINE_FIELD_HPP
#define MINESWEEPER_MINE_FIELD_HPP


#include "core/core.hpp"
#include "mine_cell.hpp"
#include "ui/scene.hpp"
#include <vector>

#define MARGIN_BY_SIDE_RADIO 0.3

class MineField {
private:
    GameCore game_core_;
    std::vector<std::shared_ptr<MineCell>> cells_;

    int field_length_;
    int field_height_;
    int num_mines_;

public:
    MineField(int field_length, int field_height, int num_mines, sf::Vector2f position, float cell_side_length);

    GameState update(sf::RenderWindow &window);

    void reset();

    void registerAsWidget(Scene &scene);
};


#endif //MINESWEEPER_MINE_FIELD_HPP
