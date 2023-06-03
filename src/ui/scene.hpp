#ifndef MINESWEEPER_SCENE_HPP
#define MINESWEEPER_SCENE_HPP


#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>


class Scene {
private:
    std::vector<std::shared_ptr<sf::Drawable>> widgets_{};

protected:
    sf::RenderWindow &window_;

    void changeScene(std::shared_ptr<Scene> target_scene);

    void registerWidget(const std::shared_ptr<sf::Drawable> &drawable);

    float win_width_{};

public:
    std::shared_ptr<Scene> next_scene = nullptr;

public:
    explicit Scene(sf::RenderWindow &window) : window_(window) {
        win_width_ = window.getSize().x;
    }

    virtual void update() = 0;

    void handleInteractions();

    void render();

public:
    void resize(sf::FloatRect area);
};


#endif //MINESWEEPER_SCENE_HPP
