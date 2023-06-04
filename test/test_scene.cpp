#include "test_scene.hpp"
#include "ui/components/mine_cell.hpp"
#include <SFML/System/Sleep.hpp>

using namespace std;
using namespace sf;

TestScene::TestScene(sf::RenderWindow &window, Difficulty::Level difficulty)
    : Scene(window, difficulty), field_(10, 10, 10, {10 DP, 10 DP}, 5 DP) {
}

void TestScene::update() {
    auto state = field_.update(window_);
    if (state == LOSE) {
        // Process lose
    }
}
