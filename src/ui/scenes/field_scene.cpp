#include "field_scene.hpp"
#include "menu_scene.hpp"
#include "ui/consts.hpp"
#include "ui/utils/clickable.hpp"
#include "ui/utils/res_pool.hpp"
#include "ui/utils/rounded.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

void FieldScene::update() {}

void FieldScene::setupUI() {
    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(DEF_WIN_WIDTH - 6 DP, DEF_WIN_HEIGHT - 16 DP), 3 DP, 4);
    round->setPosition(3 DP, 13 DP);
    round->setFillColor(sf::Color::White);
    registerWidget(round);

    // The Menu Icon
    auto menuButton = CLICKABLE(sf::RectangleShape, sf::Vector2f(6.4 DP, 6.4 DP));
    menuButton->setTexture(ResPool::getTexture("menu.png").get());
    menuButton->setPosition(4 DP, TITLE_Y);
    menuButton->setOnLeftClickHandler([this]() {
        changeScene(std::make_shared<MenuScene>(window_));
    });
    registerWidget(menuButton);

    // The Restart Icon
    auto restartButton = CLICKABLE(sf::RectangleShape, sf::Vector2f(6.4 DP, 6.4 DP));
    restartButton->setTexture(ResPool::getTexture("restart.png").get());
    restartButton->setPosition(DEF_WIN_WIDTH - 21 DP, TITLE_Y);
    restartButton->setOnLeftClickHandler([this]() {
        // Restart
    });
    registerWidget(restartButton);

    // The Exit Icon
    auto exitButton = MAKE_CLICKABLE(std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP)));
    exitButton->setTexture(ResPool::getTexture("exit.png").get());
    exitButton->setPosition(DEF_WIN_WIDTH - 10.4 DP, TITLE_Y);
    exitButton->setOnLeftClickHandler([this]() {
        exit(0);
    });
    registerWidget(exitButton);

    // The Title
    sf::Text title;
    title.setFont(*ResPool::getFont("shsmin.ttf"));
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
