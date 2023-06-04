#ifndef MINESWEEPER_MINE_CELL_HPP
#define MINESWEEPER_MINE_CELL_HPP

#include "rounded.hpp"
#include "ui/components/clickable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class MineCell : public sf::RectangleShape, public Clickable {
public:
    MineCell(sf::RenderWindow &window, sf::Vector2f position, sf::Vector2f size);
};


#endif //MINESWEEPER_MINE_CELL_HPP
