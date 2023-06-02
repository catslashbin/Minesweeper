#include "menu_scene.hpp"
#include "field_scene.hpp"
#include "ui/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void MenuScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Trigger scene change
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        // The Back Icon
        if (position.x ARCDP >= 8 && position.x ARCDP <= 13 && position.y ARCDP >= 7 && position.y ARCDP <= 14) {
            changeScene(std::make_shared<FieldScene>(window_, 10, 10, 10));
        }
    }
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    // Do some initialization

    // Background Color
    auto rect = std::make_shared<sf::RectangleShape>(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT));
    rect->setFillColor(TITLE_BG_COLOR);
    drawables_.push_back(rect);

    // Font
    auto font = ResPool::getInstance().getFont("shsmin.ttf");

    // The Back Icon
    auto backRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto backTexture = ResPool::getInstance().getTexture("back.png");
    backRect->setTexture(backTexture.get());
    backRect->setPosition(8 DP, 7 DP);
    drawables_.push_back(backRect);

    // The Title
    sf::Text title;
    title.setFont(*font);
    title.setString(L"菜单");
    title.setCharacterSize(5.1 DP);
    title.setFillColor(TITLE_COLOR);
    title.setPosition(20 DP, 7 DP);
    auto titleDrawable = std::make_shared<sf::Text>(title);
    drawables_.push_back(titleDrawable);

    // The Rounded Center Part
    auto round = std::make_shared<sf::RectangleShape>(sf::Vector2f(WIN_WIDTH - 24 DP, WIN_HEIGHT - 40 DP));
    round->setPosition(12 DP, 24 DP);
    round->setFillColor(sf::Color::White);
    drawables_.push_back(round);
}