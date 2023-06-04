#ifndef MINESWEEPER_TEST_SCENE_HPP
#define MINESWEEPER_TEST_SCENE_HPP

#include "ui/scene.hpp"

class TestScene : public Scene {
public:
    TestScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;
};


#endif //MINESWEEPER_TEST_SCENE_HPP
