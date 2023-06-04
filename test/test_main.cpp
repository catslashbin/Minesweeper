#define PRIVATE_BUT_DEBUG_PUBLIC public

#include "test_scene.hpp"
#include "ui/game.hpp"

int main()
{
    Game game;
    game._curr_scene = std::make_shared<TestScene>(game.window, Difficulty::Easy);
    game.start();
    return 0;
}