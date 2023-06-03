#include "field_scene.hpp"
#include "menu_scene.hpp"
#include "ui/utils/clickable.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include "ui/utils/rounded.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

void FieldScene::update() {}

void FieldScene::setupUI() {
    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(win_width_ - 6 DP, DEF_WIN_HEIGHT - 16 DP), 3 DP, 4);
    round->setPosition(3 DP, 13 DP);
    round->setFillColor(sf::Color::White);
    registerWidget(round);

    // The Menu Icon
    auto menuButton = CLICKABLE(sf::RectangleShape, sf::Vector2f(6.4 DP, 6.4 DP));
    menuButton->setTexture(ResPool::getTexture("menu.png").get());
    menuButton->setPosition(4 DP, TITLE_Y);
    menuButton->setOnLeftClickHandler([this]() {
        changeScene(std::make_shared<MenuScene>(window_, difficulty_));
    });
    registerWidget(menuButton);

    // The Restart Icon
    auto restartButton = CLICKABLE(sf::RectangleShape, sf::Vector2f(6.4 DP, 6.4 DP));
    restartButton->setTexture(ResPool::getTexture("restart.png").get());
    restartButton->setPosition(win_width_ - 21 DP, TITLE_Y);
    restartButton->setOnLeftClickHandler([this]() {
        // Restart
    });
    registerWidget(restartButton);

    // The Exit Icon
    auto exitButton = MAKE_CLICKABLE(std::make_shared<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP)));
    exitButton->setTexture(ResPool::getTexture("exit.png").get());
    exitButton->setPosition(win_width_ - 10.4 DP, TITLE_Y);
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

FieldScene::FieldScene(sf::RenderWindow &window, Difficulty::Level difficulty)
    : Scene(window, difficulty), mine_field_(Difficulty::MineData[difficulty][0], Difficulty::MineData[difficulty][1], Difficulty::MineData[difficulty][2]) {

    setupUI();
}
