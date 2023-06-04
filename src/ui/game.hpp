#ifndef MINESWEEPER_GAME_HPP
#define MINESWEEPER_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "scene.hpp"

#ifndef PRIVATE_BUT_DEBUG_PUBLIC
#define PRIVATE_BUT_DEBUG_PUBLIC private
#endif

class Game {
PRIVATE_BUT_DEBUG_PUBLIC:
    std::shared_ptr<Scene> _curr_scene;

public:
    sf::RenderWindow window;

    explicit Game();

    void mainLoop();

    void start();
};


#endif //MINESWEEPER_GAME_HPP
