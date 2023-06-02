#include "game.hpp"
#include "consts.hpp"
#include "ui/scenes/field_scene.hpp"
#include "ui/scenes/menu_scene.hpp"

#include <cassert>
#include <memory>
#include <SFML/Window/Event.hpp>

Game::Game() : window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE, sf::Style::None) {}

void Game::mainLoop() {

    sf::Event event{};
    sf::Vector2i grabbedOffset;
    bool grabbedWindow = false;
    while (window.isOpen()) {

        // Handle events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Draggable borderless window
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                    grabbedWindow = true;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    grabbedWindow = false;
            } else if (event.type == sf::Event::MouseMoved) {
                if (grabbedWindow)
                    window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
            }
        }

        window.clear(sf::Color::White);

        // Update scene
        assert(_curr_scene != nullptr);
        _curr_scene->update();

        if (_curr_scene->has_returned) {
            // Switch scene
            _curr_scene = _curr_scene->next_scene;
        } else {
            // Render current scene
            _curr_scene->render();
        }

        window.display();
    }
}

void Game::start() {

    info("MineSweeper start.");

    // Initialize current scene as Menu
    _curr_scene = std::make_shared<FieldScene>(window, 10, 10, 10);

    // Enable vertical sync
    window.setVerticalSyncEnabled(true);

    mainLoop();
}
