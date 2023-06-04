#include "mine_field.hpp"

MineField::MineField(int field_length, int field_height, int num_mines, sf::Vector2f position, float cell_side_length)
    : game_core_(field_length, field_height, num_mines) {

    // Initialize game core
    game_core_.scatterMines(1, 1);
    game_core_.initField();

    // Initialize cells in UI
    float margin = MARGIN_BY_SIDE_RADIO * cell_side_length;
    for (int y = 0; y < field_height; ++y) {
        for (int x = 0; x < field_length; ++x) {
            cells_.emplace_back(game_core_, x, y,
                                sf::Vector2f(float(x) * (cell_side_length + margin), float(y) * (cell_side_length + margin)) + position,
                                cell_side_length);
        }
    }
}

void MineField::update(sf::RenderWindow &window) {
    for (auto &c: cells_) {
        c.update_cell(window);
    }
}
