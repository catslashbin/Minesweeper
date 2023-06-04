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

    setOnLeftClickHandler([=, &game_core] {
        info("Reveal cell: {}, {}", x, y);
        game_core.revealCell(x, y);
    });

    setOnRightClickHandler([=, &game_core] {
        switch (game_core.getCell(x, y)->cell_state) {
            case HIDDEN:
                game_core.markFlagCell(x, y);
                break;
            case FLAGGED:
                game_core.markUnknownCell(x, y);
                break;
            case UNKNOWN:
                game_core.clearMarkCell(x, y);
                break;
            default:
                break;
        }
    });

    setOnDoubleClickHandler([=, &game_core] {
        game_core.revealSurrCells(x, y);
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
            setTexture(ResPool::getTexture("questionmark.png").get());
            break;
    }

    if (game_core_.state == LOSE && c->is_mine)
        setTexture(ResPool::getTexture("mine.png").get());

    // Draw cell
    window.draw(*this);
}
