#ifndef MINESWEEPER_SCENE_HPP
#define MINESWEEPER_SCENE_HPP


#include "ui/utils/difficulty.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>


class Scene {
private:
    std::vector<std::shared_ptr<sf::Drawable>> widgets_{};

protected:
    sf::RenderWindow &window_;

    void changeScene(std::shared_ptr<Scene> target_scene);

    float win_width_{}, win_height_{};

    Difficulty::Level difficulty_;

public:
    void registerWidget(const std::shared_ptr<sf::Drawable> &drawable);

public:
    std::shared_ptr<Scene> next_scene = nullptr;

public:
    explicit Scene(sf::RenderWindow &window, Difficulty::Level difficulty);

    virtual void update() = 0;

    void handleInteractions();

    void render();

    void resize(sf::Vector2f area);
};

#endif //MINESWEEPER_SCENE_HPP
