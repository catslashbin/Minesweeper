#ifndef MINESWEEPER_SCENE_HPP
#define MINESWEEPER_SCENE_HPP


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>


class Scene {
protected:
    sf::RenderWindow &_window;

    void changeScene(std::shared_ptr<Scene> target_scene);

public:
    std::shared_ptr<Scene> next_scene = nullptr;
    bool has_returned = false;

    explicit Scene(sf::RenderWindow &window) : _window(window) {}

    virtual void update() = 0;
};


#endif //MINESWEEPER_SCENE_HPP
