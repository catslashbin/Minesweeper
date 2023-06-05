#include "menu_scene.hpp"
#include "custom_scene.hpp"
#include "field_scene.hpp"
#include "ui/components/clickable.hpp"
#include "ui/components/rounded.hpp"
#include "ui/utils/consts.hpp"
#include "ui/utils/res_pool.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

void MenuScene::update() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2 position = sf::Mouse::getPosition(window_);
        if (position.x DP_INV >= 12 && position.x <= DEF_WIN_WIDTH - 12 DP) {
            // Easy
            bool toChangeSceneNotCustom = false;
            if (position.y DP_INV >= 28 && position.y DP_INV <= 37) {
                difficulty_ = Difficulty::Easy;
                toChangeSceneNotCustom = true;
            }
            // Medium
            if (position.y DP_INV >= 42 && position.y DP_INV <= 51) {
                difficulty_ = Difficulty::Medium;
                toChangeSceneNotCustom = true;
            }
            // Hard
            if (position.y DP_INV >= 56 && position.y DP_INV <= 65) {
                difficulty_ = Difficulty::Hard;
                toChangeSceneNotCustom = true;
            }
            if (toChangeSceneNotCustom) {
                resize(sf::Vector2f(Difficulty::WindowSize[difficulty_][0], Difficulty::WindowSize[difficulty_][1]));
                changeScene(std::make_shared<FieldScene>(window_, difficulty_));
            }
            // Custom
            if (position.y DP_INV >= 73 && position.y DP_INV <= 82) {
                changeScene(std::make_shared<CustomScene>(window_, difficulty_));
            }
        }
    }
}

void MenuScene::setupUI() {
    // Do some initialization

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
        changeScene(std::make_shared<FieldScene>(window_, difficulty_));
    });
    registerWidget(backRect);

    // The Title
    sf::Text title;
    title.setFont(*font);
    title.setString(L"菜单");
    title.setCharacterSize(static_cast<unsigned int>(5.1 DP));
    title.setFillColor(COLOR_TITLE);
    title.setPosition(20 DP, 12 DP);
    registerWidget(std::make_shared<sf::Text>(title));

    // Difficulty Labels
    sf::Text easy;
    easy.setFont(*font);
    easy.setString(L"简单");
    easy.setCharacterSize(static_cast<unsigned int>(4.3 DP));
    easy.setFillColor(COLOR_TITLE);
    easy.setPosition(14 DP, 28 DP);
    registerWidget(std::make_shared<sf::Text>(easy));

    sf::Text easyBelow = easy;
    easyBelow.setString(L"9x9棋盘 10个雷");
    easyBelow.setCharacterSize(3 DP);
    easyBelow.setFillColor(COLOR_SECONDARY);
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

    sf::Text hard = easy;
    hard.setString(L"困难");
    hard.setPosition(14 DP, 56 DP);
    registerWidget(std::make_shared<sf::Text>(hard));

    sf::Text hardBelow = easyBelow;
    hardBelow.setString(L"16x30棋盘 99个雷");
    hardBelow.setPosition(14 DP, 62 DP);
    registerWidget(std::make_shared<sf::Text>(hardBelow));

    // The Split Line
    auto line = std::make_shared<sf::RectangleShape>(sf::Vector2f(DEF_WIN_WIDTH - 10 DP, 0.5 DP));
    line->setPosition(5 DP, 69 DP);
    line->setFillColor(COLOR_TITLE_BG);
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

    // About Text
    sf::Text proudly = easyBelow;
    proudly.setString("Developed by Group 34 (Catslashbin / Tianzeds). ");
    proudly.setPosition(14 DP, 95 DP);
    proudly.setCharacterSize(static_cast<unsigned int>(2.6 DP));
    registerWidget(std::make_shared<sf::Text>(proudly));
    proudly.setString("Proudly using cross-platform very-low-level UI library SFML \n"
                      "with purely-self-written Material 3 components.");
    proudly.setPosition(14 DP, 99.5 DP);
    registerWidget(std::make_shared<sf::Text>(proudly));
}

MenuScene::MenuScene(sf::RenderWindow &window, Difficulty::Level difficulty) : Scene(window, difficulty) {
    setupUI();
}
