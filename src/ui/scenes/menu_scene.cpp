#include "menu_scene.hpp"
#include "field_scene.hpp"
#include "ui/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include "ui/utils/rounded.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void MenuScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // Trigger scene change
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        // The Back Icon
        if (position.x ARCDP >= 8 && position.x ARCDP <= 13 && position.y ARCDP >= 12 && position.y ARCDP <= 19) {
            changeScene(std::make_shared<FieldScene>(window_, 10, 10, 10));
        }
    }
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    // Do some initialization

    // Font
    auto font = ResPool::getInstance().getFont("shsmin.ttf");

    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(WIN_WIDTH - 10 DP, 60 DP), 3 DP, 4);
    round->setPosition(5 DP, 23 DP);
    round->setFillColor(sf::Color::White);
    drawables_.push_back(round);

    // The Back Icon
    auto backRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto backTexture = ResPool::getInstance().getTexture("back.png");
    backRect->setTexture(backTexture.get());
    backRect->setPosition(8 DP, 12 DP);
    drawables_.push_back(backRect);

    // The Title
    sf::Text title;
    title.setFont(*font);
    title.setString(L"菜单");
    title.setCharacterSize(5.1 DP);
    title.setFillColor(TITLE_COLOR);
    title.setPosition(20 DP, 12 DP);
    drawables_.push_back(std::make_shared<sf::Text>(title));
}