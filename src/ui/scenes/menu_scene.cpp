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
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(WIN_WIDTH - 10 DP, 65 DP), 3 DP, 4);
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

    // Difficulty Labels
    sf::Text easy;
    easy.setFont(*font);
    easy.setString(L"简单");
    easy.setCharacterSize(4.3 DP);
    easy.setFillColor(TITLE_COLOR);
    easy.setPosition(14 DP, 29 DP);
    drawables_.push_back(std::make_shared<sf::Text>(easy));

    sf::Text easyBelow = easy;
    easyBelow.setString(L"9x9棋盘 10个雷");
    easyBelow.setCharacterSize(3 DP);
    easyBelow.setFillColor(SECONDARY_COLOR);
    easyBelow.setPosition(14 DP, 35 DP);
    drawables_.push_back(std::make_shared<sf::Text>(easyBelow));

    sf::Text medium = easy;
    medium.setString(L"中级");
    medium.setPosition(14 DP, 43 DP);
    drawables_.push_back(std::make_shared<sf::Text>(medium));

    sf::Text mediumBelow = easyBelow;
    mediumBelow.setString(L"16x16棋盘 40个雷");
    mediumBelow.setPosition(14 DP, 49 DP);
    drawables_.push_back(std::make_shared<sf::Text>(mediumBelow));

    sf::Text diff = easy;
    diff.setString(L"困难");
    diff.setPosition(14 DP, 57 DP);
    drawables_.push_back(std::make_shared<sf::Text>(diff));

    sf::Text diffBelow = easyBelow;
    diffBelow.setString(L"16x30棋盘 99个雷");
    diffBelow.setPosition(14 DP, 63 DP);
    drawables_.push_back(std::make_shared<sf::Text>(diffBelow));

    // The Split Line
    auto line = std::make_shared<sf::RectangleShape>(sf::Vector2f(WIN_WIDTH - 10 DP, 0.5 DP));
    line->setPosition(5 DP, 70 DP);
    line->setFillColor(TITLE_BG_COLOR);
    drawables_.push_back(line);

    sf::Text custom = easy;
    custom.setString(L"自定义");
    custom.setPosition(14 DP, 74 DP);
    drawables_.push_back(std::make_shared<sf::Text>(custom));

    sf::Text customBelow = easyBelow;
    customBelow.setString(L"自定义棋盘大小和雷数");
    customBelow.setPosition(14 DP, 80 DP);
    drawables_.push_back(std::make_shared<sf::Text>(customBelow));
}