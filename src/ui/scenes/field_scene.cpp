#include "field_scene.hpp"
#include "ui/consts.hpp"

FieldScene::FieldScene(sf::RenderWindow &window, int field_length, int field_height, int num_mines)
    : Scene(window) { //, mine_field_(field_length, field_height, num_mines) {
}

void FieldScene::update() {
    sf::CircleShape circle(20 DP);
    circle.setFillColor(sf::Color::Red);
    _window.draw(circle);
}
