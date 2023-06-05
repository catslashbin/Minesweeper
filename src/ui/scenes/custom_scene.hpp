#ifndef MINESWEEPER_CUSTOM_SCENE_HPP
#define MINESWEEPER_CUSTOM_SCENE_HPP

#include "ui/components/rounded.hpp"
#include "ui/scene.hpp"
#include "ui/utils/difficulty.hpp"
#include <SFML/Graphics/Text.hpp>

class CustomScene : public Scene {
private:
    int length_ = 12, height_ = 12, num_mines_ = 40;
    std::shared_ptr<sf::Text> l1_drawable_, l2_drawable_, l3_drawable_;
    std::shared_ptr<sf::RoundedRectangleShape> round_drawable_;

public:
    using Scene::changeScene;

    explicit CustomScene(sf::RenderWindow &window, Difficulty::Level difficulty);

    void update() override;

    void setupUI();
};


#endif //MINESWEEPER_CUSTOM_SCENE_HPP
