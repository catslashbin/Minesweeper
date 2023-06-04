#ifndef MINESWEEPER_FIELD_SCENE_HPP
#define MINESWEEPER_FIELD_SCENE_HPP

#include "ui/components/mine_field.hpp"
#include "ui/scene.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/difficulty.hpp"

class FieldScene : public Scene {
private:
    MineField field_;
    GameState sceneState_;

public:
    FieldScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;

    void setupUI();
};


#endif //MINESWEEPER_FIELD_SCENE_HPP
