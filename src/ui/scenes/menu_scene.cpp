#include "menu_scene.hpp"
#include "field_scene.hpp"
#include "ui/consts.hpp"

void MenuScene::update() {

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Trigger scene change
        sf::Vector2 position = sf::Mouse::getPosition(_window);
        if(position.x ARCDP >= 32) {
            changeScene(std::make_shared<FieldScene>(_window, 10, 10, 10));
        }
    }
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    // Do some initialization
}