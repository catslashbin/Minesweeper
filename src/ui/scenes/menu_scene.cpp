#include "menu_scene.hpp"

void MenuScene::start(std::shared_ptr<Intent> intent) {
    MenuReturnIntent return_intent{};

    return_intent.field_width = 10;
    return_intent.field_height = 10;
    return_intent.num_mines = 5;

    return std::make_shared<MenuReturnIntent>(return_intent);
}

void MenuScene::update() {
    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Green);
    _window.draw(circle);
}
