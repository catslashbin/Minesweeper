#ifndef MINESWEEPER_MENU_SCENE_HPP
#define MINESWEEPER_MENU_SCENE_HPP

#include "ui/scene.hpp"

class MenuScene : public Scene {
public:
    using Scene::Scene;
    using Scene::changeScene;

    void start(std::shared_ptr<Intent> intent) override;

    void update() override;
};


#endif //MINESWEEPER_MENU_SCENE_HPP
