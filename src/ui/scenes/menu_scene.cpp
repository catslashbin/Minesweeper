#include "menu_scene.hpp"
#include "field_scene.hpp"
#include "ui/consts.hpp"

void MenuScene::update() {

    sf::CircleShape circle(20 DP);
    circle.setFillColor(sf::Color::Green);
    _window.draw(circle);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Trigger scene change
        changeScene(std::make_shared<FieldScene>(_window, 10, 10, 10));
    }
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    // Do some initialization
}
