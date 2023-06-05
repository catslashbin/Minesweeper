#include "custom_scene.hpp"
#include "menu_scene.hpp"
#include "ui/components/clickable.hpp"
#include "ui/components/rounded.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void CustomScene::update() {
    window_.draw(*round_drawable_);
    l1_drawable_->setString(std::to_string(length_));
    window_.draw(*l1_drawable_);
    l2_drawable_->setString(std::to_string(height_));
    window_.draw(*l2_drawable_);
    l3_drawable_->setString(std::to_string(num_mines_));
    window_.draw(*l3_drawable_);
}

void CustomScene::setupUI() {
    // Font
    auto font = ResPool::getFont("sans.ttf");

    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(win_width_ - 10 DP, 46 DP), 3 DP, 4);
    round->setPosition(5 DP, 23 DP);
    round->setFillColor(sf::Color::White);
    round_drawable_ = round;

    // The Back Icon
    auto backRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(6.4 DP, 6.4 DP));
    backRect->setTexture(ResPool::getTexture("back.png").get());
    backRect->setPosition(8 DP, 12 DP);
    backRect->setOnLeftClickHandler([this] {
        resize(sf::Vector2f(Difficulty::WindowSize[difficulty_][0], Difficulty::WindowSize[difficulty_][1]));
        changeScene(std::make_shared<MenuScene>(window_, difficulty_));
    });
    registerWidget(backRect);

    // The Title
    sf::Text title;
    title.setFont(*font);
    title.setString(L"自定义");
    title.setCharacterSize(static_cast<unsigned int>(5.1 DP));
    title.setFillColor(COLOR_TITLE);
    title.setPosition(20 DP, 12 DP);
    registerWidget(std::make_shared<sf::Text>(title));

    sf::Text l1;
    l1.setFont(*font);
    l1.setString(L"行数");
    l1.setCharacterSize(static_cast<unsigned int>(4.3 DP));
    l1.setFillColor(COLOR_TITLE);
    l1.setPosition(14 DP, 29 DP);
    registerWidget(std::make_shared<sf::Text>(l1));

    sf::Text l1Num = l1;
    l1Num.setString(std::to_string(length_));
    l1Num.setCharacterSize(static_cast<unsigned int>(4.7 DP));
    l1Num.setPosition(36 DP, 28.7 DP);
    l1_drawable_ = std::make_shared<sf::Text>(l1Num);

    auto l1AddRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(5 DP, 5 DP));
    l1AddRect->setTexture(ResPool::getTexture("add.png").get());
    l1AddRect->setPosition(win_width_ - 27 DP, 29 DP);
    l1AddRect->setOnLeftClickHandler([this] {
        length_++;
    });
    registerWidget(l1AddRect);

    auto l1MinusRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(5 DP, 5 DP));
    l1MinusRect->setTexture(ResPool::getTexture("minus.png").get());
    l1MinusRect->setPosition(win_width_ - 19 DP, 29 DP);
    l1MinusRect->setOnLeftClickHandler([this] {
        if (length_ >= 6) length_--;
    });
    registerWidget(l1MinusRect);

    sf::Text l2 = l1;
    l2.setString(L"列数");
    l2.setPosition(14 DP, 43 DP);
    registerWidget(std::make_shared<sf::Text>(l2));

    sf::Text l2Num = l1Num;
    l2Num.setString(std::to_string(height_));
    l2Num.setPosition(36 DP, 42.7 DP);
    l2_drawable_ = std::make_shared<sf::Text>(l2Num);

    auto l2AddRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(5 DP, 5 DP));
    l2AddRect->setTexture(ResPool::getTexture("add.png").get());
    l2AddRect->setPosition(win_width_ - 27 DP, 43 DP);
    l2AddRect->setOnLeftClickHandler([this] {
        height_++;
    });
    registerWidget(l2AddRect);

    auto l2MinusRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(5 DP, 5 DP));
    l2MinusRect->setTexture(ResPool::getTexture("minus.png").get());
    l2MinusRect->setPosition(win_width_ - 19 DP, 43 DP);
    l2MinusRect->setOnLeftClickHandler([this] {
        if (height_ >= 6) height_--;
    });
    registerWidget(l2MinusRect);

    sf::Text l3 = l1;
    l3.setString(L"总雷数");
    l3.setPosition(14 DP, 57 DP);
    registerWidget(std::make_shared<sf::Text>(l3));

    sf::Text l3Num = l1Num;
    l3Num.setString(std::to_string(num_mines_));
    l3Num.setPosition(36 DP, 56.7 DP);
    l3_drawable_ = std::make_shared<sf::Text>(l3Num);

    auto l3AddRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(5 DP, 5 DP));
    l3AddRect->setTexture(ResPool::getTexture("add.png").get());
    l3AddRect->setPosition(win_width_ - 27 DP, 57 DP);
    l3AddRect->setOnLeftClickHandler([this] {
        num_mines_++;
    });
    registerWidget(l3AddRect);

    auto l3MinusRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(5 DP, 5 DP));
    l3MinusRect->setTexture(ResPool::getTexture("minus.png").get());
    l3MinusRect->setPosition(win_width_ - 19 DP, 57 DP);
    l3MinusRect->setOnLeftClickHandler([this] {
        if (num_mines_ >= 5) num_mines_--;
    });
    registerWidget(l3MinusRect);

    // The Confirmation Icon
    auto confirmRect = std::make_shared<ClickableShape<sf::RectangleShape>>(sf::Vector2f(6.6 DP, 6.6 DP));
    confirmRect->setTexture(ResPool::getTexture("confirm.png").get());
    confirmRect->setPosition(14 DP, 74 DP);
    confirmRect->setOnLeftClickHandler([this] {
        info("Custom Scene: L" + std::to_string(length_) + "H" + std::to_string(height_) + ", M" + std::to_string(num_mines_));
    });
    registerWidget(confirmRect);
}

CustomScene::CustomScene(sf::RenderWindow &window, Difficulty::Level difficulty) : Scene(window, difficulty) {
    setupUI();
}
