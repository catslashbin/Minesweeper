#ifndef MINESWEEPER_MINE_CELL_HPP
#define MINESWEEPER_MINE_CELL_HPP

#include "core/core.hpp"
#include "rounded.hpp"
#include "ui/components/clickable.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

#define ROUND_RADIUS_BY_SIDE_RADIO 0.1

class MineCell : public sf::RoundedRectangleShape, public Clickable {

private:
    GameCore &game_core_;
    int x_;
    int y_;

public:
    MineCell(GameCore &game_core, int x, int y, sf::Vector2f position, float side_length);

    void updateCell(sf::RenderWindow &window);

    /**
     * @warning This function must be called immediately after constructor func.
     *          But it can not be called INSIDE the constructor, otherwise the lambda function will broken.
     */
    void setUpHandlers();
};


#endif //MINESWEEPER_MINE_CELL_HPP
