#include "menu_scene.hpp"
#include "field_scene.hpp"
#include "ui/consts.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void MenuScene::update() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Trigger scene change
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        if (position.x ARCDP >= 32) {
            changeScene(std::make_shared<FieldScene>(window_, 10, 10, 10));
        }
    }
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    // Do some initialization

    // Background Color
    auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT));
    rect->setFillColor(TITLE_BG_COLOR);
    drawables_.push_back(rect);
}