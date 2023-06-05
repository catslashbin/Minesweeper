#ifndef MINESWEEPER_CUSTOM_SCENE_HPP
#define MINESWEEPER_CUSTOM_SCENE_HPP

#include "ui/scene.hpp"
#include "ui/utils/difficulty.hpp"

class CustomScene : public Scene {
public:
    using Scene::changeScene;

    explicit CustomScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;

    void setupUI();
};


#endif //MINESWEEPER_CUSTOM_SCENE_HPP
