#include "game.hpp"
#include "consts.hpp"
#include "ui/scenes/field_scene.hpp"

#include <SFML/Window/Event.hpp>
#include <spdlog/spdlog.h>
#include <cassert>
#include <memory>

Game::Game() : window(sf::VideoMode(DEF_WIN_WIDTH, DEF_WIN_HEIGHT), "", sf::Style::Close) {}

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

        window.clear(TITLE_BG_COLOR);

        // Update scene
        assert(_curr_scene != nullptr);

        _curr_scene->handleInteractions();
        if (_curr_scene->next_scene) {
            info("Scene changed.");
            _curr_scene = _curr_scene->next_scene;
            continue;
        }

        _curr_scene->update();
        if (_curr_scene->next_scene) {
            info("Scene changed.");
            _curr_scene = _curr_scene->next_scene;
            continue;
        }

        _curr_scene->render();

        window.display();
    }
}

void Game::start() {

    info("MineSweeper start.");
    spdlog::set_level(spdlog::level::debug);

    view = window.getDefaultView();

    // Initialize current scene
    _curr_scene = std::make_shared<FieldScene>(window, 10, 10, 10);

    // Enable vertical sync
    window.setVerticalSyncEnabled(true);

    mainLoop();
}
