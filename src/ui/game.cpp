#include "game.hpp"
#include "ui/scenes/field_scene.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/difficulty.hpp"

#include <SFML/Window/Event.hpp>
#include <cassert>
#include <memory>
#include <spdlog/spdlog.h>

Game::Game() : window(sf::VideoMode(DEF_WIN_WIDTH, DEF_WIN_HEIGHT), "", sf::Style::Close) {
    // Initialize current scene
    _curr_scene = std::make_shared<FieldScene>(window, Difficulty::Easy);
}

void Game::mainLoop() {

    sf::Event event{};
    size_t fps_counter = 0;
    sf::Clock fps_clock;

    while (window.isOpen()) {

        /* Handle events */
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(COLOR_TITLE_BG);

        /* Update scene */
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

        /* Calculate game fps */
        fps_counter++;
        if (fps_clock.getElapsedTime().asSeconds() > 5) {
            debug("Current fps: {}", float(fps_counter) / 5.f);
            fps_counter = 0;
            fps_clock.restart();
        }

        window.display();
    }
}

void Game::start() {

    info("MineSweeper start.");
    spdlog::set_level(spdlog::level::debug);

    // Enable vertical sync
    window.setVerticalSyncEnabled(true);

    mainLoop();
}
