#include "field_scene.hpp"
#include "menu_scene.hpp"
#include "ui/clickable.hpp"
#include "ui/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include "ui/utils/rounded.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

void FieldScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        // // The Menu Icon
        // if (position.x ARCDP >= 4 && position.x ARCDP <= 9 && position.y ARCDP >= 3 && position.y ARCDP <= 10) {
        //     changeScene(std::make_shared<MenuScene>(window_));
        // }
        // The Exit Icon
        if (position.x ARCDP >= WIN_WIDTH ARCDP - 11 && position.x ARCDP <= WIN_WIDTH ARCDP - 4 && position.y ARCDP >= 3 && position.y ARCDP <= 10) {
            window_.close();
        }
    }
}

void FieldScene::setupUI() {
    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(WIN_WIDTH, WIN_HEIGHT + 5 DP), 10 DP, 4);
    round->setPosition(0, 13 DP);
    round->setFillColor(sf::Color::White);
    registerWidget(round);

    // The Menu Icon
    auto menuRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto menuButton = std::make_shared<Clickable>(menuRect, window_);
    menuButton->setTexture(ResPool::getTexture("menu.png").get());
    menuButton->setPosition(4 DP, TITLE_Y);
    menuButton->setOnLeftClickHandler([this]() {
        changeScene(std::make_shared<MenuScene>(window_));
    });
    registerWidget(menuButton);

    // The Restart Icon
    auto restartRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    restartRect->setTexture(ResPool::getTexture("restart.png").get());
    restartRect->setPosition(WIN_WIDTH - 21 DP, TITLE_Y);
    registerWidget(restartRect);

    // The Exit Icon
    auto exitRect = std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    auto exitTexture = ResPool::getTexture("exit.png");
    exitRect->setTexture(exitTexture.get());
    exitRect->setPosition(WIN_WIDTH - 10.4 DP, TITLE_Y);
    registerWidget(exitRect);

    // The Title
    sf::Text title;
    auto font = ResPool::getFont("shsmin.ttf");
    title.setFont(*font);
    title.setString(L"扫雷");
    title.setCharacterSize(5.1 DP);
    title.setFillColor(TITLE_COLOR);
    title.setPosition(16 DP, TITLE_Y);
    auto titleDrawable = std::make_shared<sf::Text>(title);
    registerWidget(titleDrawable);
}

FieldScene::FieldScene(sf::RenderWindow &window, int field_length, int field_height, int num_mines)
    : Scene(window), mine_field_(field_length, field_height, num_mines) {

    setupUI();
}
