#ifndef MINESWEEPER_FIELD_SCENE_HPP
#define MINESWEEPER_FIELD_SCENE_HPP

#include "core/core.hpp"
#include "ui/scene.hpp"

class FieldScene : public Scene {
private:
    CORE::MineField mine_field_;

public:
    FieldScene(sf::RenderWindow &window, int field_length, int field_height, int num_mines);

    void update() override;
};


#endif //MINESWEEPER_FIELD_SCENE_HPP
