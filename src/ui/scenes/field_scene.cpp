#include "field_scene.hpp"
#include "menu_scene.hpp"
#include "ui/consts.hpp"
#include "ui/res_pool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

void FieldScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Trigger scene change
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        // The Menu Icon
        if (position.x ARCDP >= 4 && position.x ARCDP <= 9 && position.y ARCDP >= 3 && position.y ARCDP <= 10) {
            changeScene(std::make_shared<MenuScene>(window_));
        }
        // The Exit Icon
        if (position.x ARCDP >= WIN_WIDTH ARCDP - 11 && position.x ARCDP <= WIN_WIDTH ARCDP - 4 && position.y ARCDP >= 3 && position.y ARCDP <= 10) {
            window_.close();
        }
    }
}

FieldScene::FieldScene(sf::RenderWindow &window, int field_length, int field_height, int num_mines)
    : Scene(window), mine_field_(field_length, field_height, num_mines) {

    // Top Bar
    auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(WIN_WIDTH, 13 DP));
    rect->setFillColor(TITLE_BG_COLOR);
    drawables_.push_back(rect);

    // The Menu Icon
    auto menuRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto menuTexture = ResPool::getInstance().getTexture("menu.png");
    menuRect->setTexture(menuTexture.get());
    menuRect->setPosition(4 DP, TITLE_Y);
    drawables_.push_back(menuRect);

    // The Restart Icon
    auto restartRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto restartTexture = ResPool::getInstance().getTexture("restart.png");
    restartRect->setTexture(restartTexture.get());
    restartRect->setPosition(WIN_WIDTH - 20 DP, TITLE_Y);
    drawables_.push_back(restartRect);

    // The Exit Icon
    auto exitRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto exitTexture = ResPool::getInstance().getTexture("exit.png");
    exitRect->setTexture(exitTexture.get());
    exitRect->setPosition(WIN_WIDTH - 10.4 DP, TITLE_Y);
    drawables_.push_back(exitRect);

    // The Title
    sf::Text title;
    auto font = ResPool::getInstance().getFont("shsmin.ttf");
    title.setFont(*font);
    title.setString(L"扫雷");
    title.setCharacterSize(5.1 DP);
    title.setFillColor(TITLE_COLOR);
    title.setPosition(16 DP, TITLE_Y);
    auto titleDrawable = std::make_shared<sf::Text>(title);
    drawables_.push_back(titleDrawable);
}
