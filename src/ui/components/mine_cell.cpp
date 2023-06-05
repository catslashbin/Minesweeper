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

    setFillColor(NOT_CLICKED_COLOR);
    setCornersRadius(side_length / 10.f);
    setCornerPointCount(4);
}

void MineCell::setUpHandlers() {

    setOnLeftClickHandler([this] {
        info("Reveal cell: {}, {}", x_, y_);
        game_core_.revealCell(x_, y_);
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

    setOnHoverChangeHandler([this](bool is_hover){
        setFillColor(is_hover ? HOVER_COLOR : NOT_CLICKED_COLOR);
    });
}

void MineCell::updateCell(sf::RenderWindow &window) {
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
            setTexture(ResPool::getTexture("questionmark.png").get());
            break;
    }

    if (game_core_.state == LOSE && c->is_mine)
        setTexture(ResPool::getTexture("mine.png").get());
}
