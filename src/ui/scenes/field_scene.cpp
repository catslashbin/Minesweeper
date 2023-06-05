#include "field_scene.hpp"
#include "menu_scene.hpp"
#include "ui/components/clickable.hpp"
#include "ui/components/rounded.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void FieldScene::update() {
    // Field Render
    auto state = field_.update(window_);
    if (state == LOSE && scene_state_ == RUNNING) {
        scene_state_ = LOSE;
        info("You failed.");
    } else if (state == WIN && scene_state_ == RUNNING) {
        scene_state_ = WIN;
        info("You won the game!");
    } else if (state == RUNNING) {
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
        field_.reset();
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
    title.setFillColor(COLOR_TITLE);
    title.setPosition(16 DP, TITLE_Y);
    auto titleDrawable = std::make_shared<sf::Text>(title);
    registerWidget(titleDrawable);

    // Field Title
    sf::Text status_bar;
    status_bar.setFont(*ResPool::getFont("sans.ttf"));
    status_bar.setCharacterSize(static_cast<unsigned int>(4.4 DP));
    status_bar.setFillColor(COLOR_SECONDARY);
    status_bar.setPosition(31 DP, TITLE_Y + 0.45 DP);
    status_bar.setString(L"14 操作｜3 雷");
    auto statusDrawable = std::make_shared<sf::Text>(status_bar);
    registerWidget(statusDrawable);

    // Field
    field_.registerAsWidget(*this);
}

FieldScene::FieldScene(sf::RenderWindow &window, Difficulty::Level difficulty)
    : Scene(window, difficulty), field_(Difficulty::MineData[difficulty][1], Difficulty::MineData[difficulty][0],
                                        Difficulty::MineData[difficulty][2],
                                        {static_cast<float>(difficulty == Difficulty::Easy ? 14.1 DP : 13 DP), 18 DP},
                                        difficulty == Difficulty::Easy ? 8 DP : 4.5 DP) {

    setupUI();
    scene_state_ = RUNNING;
}
