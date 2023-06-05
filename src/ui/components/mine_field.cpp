#include "mine_field.hpp"

MineField::MineField(int field_length, int field_height, int num_mines, sf::Vector2f position, float cell_side_length)
    : game_core_(field_length, field_height, num_mines) {

    field_length_ = field_length;
    field_height_ = field_height;
    num_mines_ = num_mines;

    float margin = MARGIN_BY_SIDE_RADIO * cell_side_length;
    for (int y = 0; y < field_height_; ++y) {
        for (int x = 0; x < field_length_; ++x) {
            auto c = std::make_shared<MineCell>(game_core_, x, y,
                                               sf::Vector2f(float(x) * (cell_side_length + margin),
                                                            float(y) * (cell_side_length + margin)) +
                                                       position,
                                               cell_side_length);
            c->setUpHandlers();
            cells_.emplace_back(c);
        }
    }
}

void MineField::reset() {
    game_core_ = GameCore(field_length_, field_height_, num_mines_);
}

GameState MineField::update(sf::RenderWindow &window) {
    for (auto &c: cells_) {
        c->updateCell(window);
    }
    return game_core_.state;
}

void MineField::registerAsWidget(Scene &scene) {
    for (auto &c: cells_) {
        scene.registerWidget(c);
    }
}
