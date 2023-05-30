#include "game.hpp"
#include "consts.hpp"
#include "ui/scenes/menu_scene.hpp"
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <memory>


Game::Game() : window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE) {}

void Game::mainLoop() {

    sf::Event event{};
    while (window.isOpen()) {

        // Handle events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Update scene
        assert(_curr_scene != nullptr);
        _curr_scene->update();

        if (_curr_scene->return_intent != nullptr) {
            switch (_curr_scene->return_intent->target_intent) {

            }
        }

        window.display();
    }
}

void Game::start() {

    // Initialize current scene as Menu
    _curr_scene = std::make_shared<MenuScene>(window);

    mainLoop();
}
