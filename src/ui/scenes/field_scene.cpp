#include "field_scene.hpp"
#include "menu_scene.hpp"
#include "ui/utils/clickable.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include "ui/utils/rounded.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

void FieldScene::update() {
    // Field Title
    sf::Text title;
    title.setFont(*ResPool::getFont("sans.ttf"));
    title.setString(L"14 操作｜3 雷");
    title.setCharacterSize(static_cast<unsigned int>(4.4 DP));
    title.setFillColor(SECONDARY_COLOR);
    title.setPosition(31 DP, TITLE_Y + 0.45 DP);
    auto titleDrawable = std::make_shared<sf::Text>(title);
    registerWidget(titleDrawable);
    // Field Block
    for (int i = 0; i < Difficulty::MineData[difficulty_][1]; i++) {
        for (int j = 0; j < Difficulty::MineData[difficulty_][0]; j++) {
            float width = difficulty_ == Difficulty::Easy ? 8 DP : 4.5 DP;
            float paddingWidth = difficulty_ == Difficulty::Easy ? 11 DP : 6 DP;
            float left = difficulty_ == Difficulty::Easy ? 12 DP : 13 DP;
            float top = difficulty_ == Difficulty::Easy ? 17 DP : 18 DP;
            auto block = CLICKABLE(sf::RoundedRectangleShape, sf::Vector2f(width, width), 1 DP, 4);
            if (i == 3 && j == 4) {
                block->setTexture(ResPool::getTexture("1.png").get());
            } else if (i <= 2 && j <= 5 || i == 2 && j == 6 || i >= 8 && j <= 7) {
                block->setTexture(ResPool::getTexture("0.png").get());
            } else if (i == 3 && j == 5) {
                block->setTexture(ResPool::getTexture("5.png").get());
            } else if (i == 3 && j == 7) {
                block->setTexture(ResPool::getTexture("questionmark.png").get());
            } else if (i == 5 && j == 5) {
                block->setTexture(ResPool::getTexture("minemark.png").get());
            } else {
                block->setFillColor(NOT_CLICKED_COLOR);
            }
            block->setPosition(left + static_cast<float>(i) * paddingWidth, top + static_cast<float>(j) * paddingWidth);
            block->setOnLeftClickHandler([this]() {});
            registerWidget(block);
        }
    }
}

void FieldScene::setupUI() {
    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(win_width_ - 6 DP, DEF_WIN_HEIGHT - 16 DP), 3 DP, 4);
    round->setPosition(3 DP, 13 DP);
    round->setFillColor(sf::Color::White);
    registerWidget(round);

    // The Menu Icon
    auto menuButton = ClickableShape<sf::RectangleShape>(sf::Vector2f(6.4 DP, 6.4 DP));
    menuButton.setTexture(ResPool::getTexture("menu.png").get());
    menuButton.setPosition(4 DP, TITLE_Y);
    menuButton.setOnLeftClickHandler([this]() {
        changeScene(std::make_shared<MenuScene>(window_, difficulty_));
    });
    registerWidget(std::make_shared<ClickableShape<sf::RectangleShape>>(menuButton));

    // The Restart Icon
    auto restartButton = CLICKABLE(sf::RectangleShape, sf::Vector2f(6.4 DP, 6.4 DP));
    restartButton->setTexture(ResPool::getTexture("restart.png").get());
    restartButton->setPosition(win_width_ - 21 DP, TITLE_Y);
    restartButton->setOnLeftClickHandler([this]() {
        // Restart
    });
    registerWidget(restartButton);

    // The Exit Icon
    auto exitButton = CLICKABLE(sf::RectangleShape, sf::Vector2f(6.4 DP, 6.4 DP));
    exitButton->setTexture(ResPool::getTexture("exit.png").get());
    exitButton->setPosition(static_cast<float>(win_width_ - 10.4 DP), TITLE_Y);
    exitButton->setOnLeftClickHandler([this]() {
        exit(0);
    });
    registerWidget(exitButton);

    // The Title
    sf::Text title;
    title.setFont(*ResPool::getFont("sans.ttf"));
    title.setString(L"扫雷");
    title.setCharacterSize(static_cast<unsigned int>(5.1 DP));
    title.setFillColor(TITLE_COLOR);
    title.setPosition(16 DP, TITLE_Y);
    auto titleDrawable = std::make_shared<sf::Text>(title);
    registerWidget(titleDrawable);
}

FieldScene::FieldScene(sf::RenderWindow &window, Difficulty::Level difficulty)
    : Scene(window, difficulty), mine_field_(Difficulty::MineData[difficulty][0], Difficulty::MineData[difficulty][1], Difficulty::MineData[difficulty][2]) {

    mine_field_.initField();

    setupUI();
}
