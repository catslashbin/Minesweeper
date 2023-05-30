#ifndef MINESWEEPER_GAME_HPP
#define MINESWEEPER_GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "scene.hpp"

class Game {
private:
    std::shared_ptr<Scene> _curr_scene;

public:
    sf::RenderWindow window;

    explicit Game();

    void mainLoop();

    void start();
};


#endif //MINESWEEPER_GAME_HPP
