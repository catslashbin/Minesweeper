#ifndef MINESWEEPER_FIELD_SCENE_HPP
#define MINESWEEPER_FIELD_SCENE_HPP

#include "core/core.hpp"
#include "ui/scene.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/difficulty.hpp"

class FieldScene : public Scene {
private:
    MineField mine_field_;

public:
    FieldScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;

    void setupUI();
};


#endif //MINESWEEPER_FIELD_SCENE_HPP
