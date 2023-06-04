#include "test_scene.hpp"
#include "ui/components/mine_cell.hpp"

using namespace std;
using namespace sf;

TestScene::TestScene(sf::RenderWindow &window, Difficulty::Level difficulty)
    : Scene(window, difficulty), field_(10, 10, 10, {10 DP, 10 DP}, 5 DP) {
    field_.setupUI();
}

void TestScene::update() {
    field_.update(window_);
}
