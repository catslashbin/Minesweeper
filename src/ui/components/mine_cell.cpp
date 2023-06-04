#include "mine_cell.hpp"
#include "core/core.hpp"
#include "rounded.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"

MineCell::MineCell(GameCore &game_core, int x, int y, sf::Vector2f position, float side_length)
    : game_core_(game_core), x_(x), y_(y) {

    assert(x >= 0 && y >= 0);

    setPosition(sf::Vector2f(position));
    setSize(sf::Vector2f(side_length, side_length));

    setCornersRadius(side_length / 10.f);
    setCornerPointCount(4);

    setOnLeftClickHandler([this] {
        info("Reveal cell: {}, {}", this->x_, this->y_);
        game_core_.revealCell(this->x_, this->y_);
    });

    setOnRightClickHandler([this] {
        switch (game_core_.getCell(x_, y_)->cell_state) {
            case HIDDEN:
                game_core_.markFlagCell(x_, y_);
                break;
            case FLAGGED:
                game_core_.markUnknownCell(x_, y_);
                break;
            case UNKNOWN:
                game_core_.clearMarkCell(x_, y_);
                break;
            default:
                break;
        }
    });

    setOnDoubleClickHandler([this] {
        game_core_.revealSurrCells(x_, y_);
    });
}

void MineCell::update_cell(sf::RenderWindow &window) {
    // Handle mouse click manually
    handleInteraction(window);

    auto c = game_core_.getCell(x_, y_);
    switch (c->cell_state) {
        case REVEALED:
            setTexture(ResPool::getTexture(fmt::format("{}.png", c->num_surr_mines)).get());
            break;
        case HIDDEN:
            setTexture(nullptr);
            break;
        case FLAGGED:
            setTexture(ResPool::getTexture("minemark.png").get());
            break;
        case UNKNOWN:
            setTexture(ResPool::getTexture("questionmark").get());
            break;
    }

    // Draw cell
    window.draw(*this);
}
