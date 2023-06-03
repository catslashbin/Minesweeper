#include "menu_scene.hpp"
#include "field_scene.hpp"
#include "ui/consts.hpp"
#include "ui/utils/clickable.hpp"
#include "ui/utils/res_pool.hpp"
#include "ui/utils/rounded.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void MenuScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        if (position.x ARCDP >= 12 && position.x <= DEF_WIN_WIDTH - 12 DP) {
            // Easy
            if (position.y ARCDP >= 28 && position.y ARCDP <= 37) {
                // Selected Easy Mode
            }
            // Medium
            if (position.y ARCDP >= 42 && position.y ARCDP <= 51) {
                // Selected Medium Mode
            }
            // Hard
            if (position.y ARCDP >= 56 && position.y ARCDP <= 65) {
                // Selected Hard Mode
            }
            // Custom
            if (position.y ARCDP >= 73 && position.y ARCDP <= 82) {
                // Selected Custom Mode
            }
        }
    }
}

void MenuScene::setupUI() {
    // Do some initialization

    // Font
    auto font = ResPool::getFont("shsmin.ttf");

    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(win_width_ - 10 DP, 65 DP), 3 DP, 4);
    round->setPosition(5 DP, 23 DP);
    round->setFillColor(sf::Color::White);
    registerWidget(round);

    // The Back Icon
    auto backRect = MAKE_CLICKABLE(std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP)));
    backRect->setTexture(ResPool::getTexture("back.png").get());
    backRect->setPosition(8 DP, 12 DP);
    backRect->setOnLeftClickHandler([this] {
        changeScene(std::make_shared<FieldScene>(window_, 10, 10, 10));
    });
    registerWidget(backRect);

    // The Title
    sf::Text title;
    title.setFont(*font);
    title.setString(L"菜单");
    title.setCharacterSize(5.1 DP);
    title.setFillColor(TITLE_COLOR);
    title.setPosition(20 DP, 12 DP);
    registerWidget(std::make_shared<sf::Text>(title));

    // Difficulty Labels
    sf::Text easy;
    easy.setFont(*font);
    easy.setString(L"简单");
    easy.setCharacterSize(4.3 DP);
    easy.setFillColor(TITLE_COLOR);
    easy.setPosition(14 DP, 28 DP);
    registerWidget(std::make_shared<sf::Text>(easy));

    sf::Text easyBelow = easy;
    easyBelow.setString(L"9x9棋盘 10个雷");
    easyBelow.setCharacterSize(3 DP);
    easyBelow.setFillColor(SECONDARY_COLOR);
    easyBelow.setPosition(14 DP, 34 DP);
    registerWidget(std::make_shared<sf::Text>(easyBelow));

    sf::Text medium = easy;
    medium.setString(L"中级");
    medium.setPosition(14 DP, 42 DP);
    registerWidget(std::make_shared<sf::Text>(medium));

    sf::Text mediumBelow = easyBelow;
    mediumBelow.setString(L"16x16棋盘 40个雷");
    mediumBelow.setPosition(14 DP, 48 DP);
    registerWidget(std::make_shared<sf::Text>(mediumBelow));

    sf::Text diff = easy;
    diff.setString(L"困难");
    diff.setPosition(14 DP, 56 DP);
    registerWidget(std::make_shared<sf::Text>(diff));

    sf::Text diffBelow = easyBelow;
    diffBelow.setString(L"16x30棋盘 99个雷");
    diffBelow.setPosition(14 DP, 62 DP);
    registerWidget(std::make_shared<sf::Text>(diffBelow));

    // The Split Line
    auto line = std::make_shared<sf::RectangleShape>(sf::Vector2f(DEF_WIN_WIDTH - 10 DP, 0.5 DP));
    line->setPosition(5 DP, 69 DP);
    line->setFillColor(TITLE_BG_COLOR);
    registerWidget(line);

    sf::Text custom = easy;
    custom.setString(L"自定义");
    custom.setPosition(14 DP, 73 DP);
    registerWidget(std::make_shared<sf::Text>(custom));

    sf::Text customBelow = easyBelow;
    customBelow.setString(L"自定义棋盘大小和雷数");
    customBelow.setPosition(14 DP, 79 DP);
    registerWidget(std::make_shared<sf::Text>(customBelow));

    // The Forth Icon
    auto forthRect = sf::RectangleShape(sf::Vector2f(6 DP, 6 DP));
    forthRect.setTexture(ResPool::getTexture("forth.png").get());
    forthRect.setPosition(win_width_ - 17 DP, 75 DP);
    registerWidget(std::make_shared<sf::RectangleShape>(forthRect));
}

MenuScene::MenuScene(sf::RenderWindow &window) : Scene(window) {
    sf::FloatRect visibleArea(0, 0, static_cast<float>(90 DP),
                              static_cast<float>(120 DP));
    resize(visibleArea);

    setupUI();
}
