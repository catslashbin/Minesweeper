#ifndef MINESWEEPER_TEST_SCENE_HPP
#define MINESWEEPER_TEST_SCENE_HPP

#include "ui/components/mine_field.hpp"
#include "ui/scene.hpp"

class TestScene : public Scene {
private:
    MineField field_;

public:
    TestScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;
};


#endif //MINESWEEPER_TEST_SCENE_HPP
