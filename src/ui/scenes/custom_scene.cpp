#include "custom_scene.hpp"
#include "menu_scene.hpp"
#include "ui/components/clickable.hpp"
#include "ui/components/rounded.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void CustomScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        if (position.x DP_INV >= 12 && position.x <= DEF_WIN_WIDTH - 12 DP) {
        }
    }
}

void CustomScene::setupUI() {
    // Font
    auto font = ResPool::getFont("sans.ttf");

    // The Rounded Center Part
    auto round = std::make_shared<sf::RoundedRectangleShape>(sf::Vector2f(win_width_ - 10 DP, 65 DP), 3 DP, 4);
    round->setPosition(5 DP, 23 DP);
    round->setFillColor(sf::Color::White);
    registerWidget(round);

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

    // About Text
    sf::Text proudly;
    proudly.setFillColor(COLOR_SECONDARY);
    proudly.setString("Developed by Group 34 (Catslashbin / Tianzeds). ");
    proudly.setPosition(14 DP, 95 DP);
    proudly.setCharacterSize(static_cast<unsigned int>(2.6 DP));
    registerWidget(std::make_shared<sf::Text>(proudly));
    proudly.setString("Proudly using cross-platform very-low-level UI library SFML \n"
                      "with purely-self-written Material 3 components.");
    proudly.setPosition(14 DP, 99.5 DP);
    registerWidget(std::make_shared<sf::Text>(proudly));
}

CustomScene::CustomScene(sf::RenderWindow &window, Difficulty::Level difficulty) : Scene(window, difficulty) {
    setupUI();
}
