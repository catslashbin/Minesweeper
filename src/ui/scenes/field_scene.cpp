#include "field_scene.hpp"
#include "menu_scene.hpp"

#include "ui/components/clickable.hpp"
#include "ui/components/rounded.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <fmt/xchar.h>

void FieldScene::update() {
    // Field Render
    auto state = field_.update();
    if (state.status == LOSE && scene_state_ == RUNNING) {
        scene_state_ = LOSE;
    } else if (state.status == WIN && scene_state_ == RUNNING) {
        scene_state_ = WIN;
        time_win_ = state.time.asSeconds();
    }
    if (state.status == LOSE) {
        status_drawable_->setFillColor(COLOR_MINE);
        status_drawable_->setString(L"游戏结束");
        window_.draw(*status_drawable_);
    } else if (state.status == WIN) {
        status_drawable_->setFillColor(COLOR_WIN);
        if (time_win_ == 0) time_win_ = state.time.asSeconds();
        status_drawable_->setString(fmt::format(L"胜利！用时 {:.2f} 秒", time_win_));
        window_.draw(*status_drawable_);
    } else if (state.status == RUNNING) {
        status_drawable_->setFillColor(COLOR_SECONDARY);
        status_drawable_->setString(
                fmt::format(L"{:.2f} 秒｜{} 雷", state.time.asSeconds(), state.num_remaining_mines));
        window_.draw(*status_drawable_);
    }
}

void FieldScene::setupUI() {
    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(win_width_ - 6 DP, win_height_ - 16 DP), 3 DP, 4);
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
    status_drawable_ = std::make_shared<sf::Text>(status_bar);

    // Field
    field_.registerAsWidget(*this);
}

FieldScene::FieldScene(sf::RenderWindow &window, Difficulty::Level difficulty)
    : Scene(window, difficulty), field_(Difficulty::MineData[difficulty][1], Difficulty::MineData[difficulty][0],
                                        Difficulty::MineData[difficulty][2],
                                        {static_cast<float>(difficulty == Difficulty::Easy ? 14.1 DP : 13 DP),
                                         static_cast<float>(difficulty == Difficulty::Easy ? 20 DP : 18 DP)},
                                        difficulty == Difficulty::Easy ? 8 DP : 4.5 DP) {
    setupUI();
    scene_state_ = RUNNING;
}

FieldScene::FieldScene(sf::RenderWindow &window, int length, int height, int num_mines)
    : Scene(window, Difficulty::Custom), field_(length, height,
                                                num_mines, {13 DP, 18.5f DP + static_cast<float>(height) * 0.2f DP},
                                                static_cast<float>(8 DP) / static_cast<float>(length + height) * 18) {
    float cellSideLength = static_cast<float>(8 DP) / static_cast<float>(length + height) * 18;
    resize(sf::Vector2f(std::max(static_cast<float>(94 DP), cellSideLength * static_cast<float>(length) * 1.33f + 23 DP),
                        cellSideLength * static_cast<float>(height) * 1.33f + 29 DP));
    setupUI();
    scene_state_ = RUNNING;
}
