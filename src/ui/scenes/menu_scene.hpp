#ifndef MINESWEEPER_MENU_SCENE_HPP
#define MINESWEEPER_MENU_SCENE_HPP

#include "ui/scene.hpp"

class MenuScene : public Scene {
public:
    using Scene::changeScene;

    explicit MenuScene(sf::RenderWindow &window);

    void update() override;
};


#endif //MINESWEEPER_MENU_SCENE_HPP
