#include "mine_cell.hpp"
#include "rounded.hpp"

MineCell::MineCell(sf::RenderWindow &window, sf::Vector2f position, sf::Vector2f size)
    : Clickable(std::make_shared<sf::RoundedRectangleShape>(), window) {
    Clickable::setPosition(position);
    setSize(size);
}
