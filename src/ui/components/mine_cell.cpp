#include "mine_cell.hpp"
#include "rounded.hpp"

MineCell::MineCell(sf::RenderWindow &window, sf::Vector2f position, sf::Vector2f size) {
    setPosition(position);
    setSize(size);
}
