#ifndef MINESWEEPER_SCENE_HPP
#define MINESWEEPER_SCENE_HPP

#include "game.hpp"
#include "intents.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>


class Scene {
protected:
    sf::RenderWindow &_window;

    void changeScene(std::shared_ptr<Intent> intent);

public:
    std::shared_ptr<Intent> return_intent = nullptr;

    explicit Scene(sf::RenderWindow &window) : _window(window) {}

    virtual void start(std::shared_ptr<Intent> intent) = 0;

    virtual void update() = 0;
};


#endif //MINESWEEPER_SCENE_HPP
