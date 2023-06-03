#ifndef MINESWEEPER_MENU_SCENE_HPP
#define MINESWEEPER_MENU_SCENE_HPP

#include "ui/scene.hpp"
#include "ui/utils/difficulty.hpp"

class MenuScene : public Scene {
public:
    using Scene::changeScene;

    explicit MenuScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;

    void setupUI();
};


#endif //MINESWEEPER_MENU_SCENE_HPP
