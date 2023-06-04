#ifndef MINESWEEPER_TEST_SCENE_HPP
#define MINESWEEPER_TEST_SCENE_HPP

#include "ui/scene.hpp"

class TestScene : Scene {
public:
    TestScene(sf::RenderWindow &window_1, Difficulty::Level difficulty, sf::RenderWindow &window);

    void update() override;
};


#endif //MINESWEEPER_TEST_SCENE_HPP
