
#include "scene.hpp"
#include "ui/utils/clickable.hpp"
#include "ui/utils/consts.hpp"

#include <cassert>
#include <utility>

void Scene::changeScene(std::shared_ptr<Scene> target_scene) {
    debug("Trigger scene change");
    next_scene = std::move(target_scene);
}

void Scene::registerWidget(const std::shared_ptr<sf::Drawable> &widget) {
    widgets_.push_back(widget);
}

void Scene::handleInteractions() {
    for (const auto &d: widgets_) {
        if (auto c = dynamic_cast<Clickable *>(d.get())) {
            c->handleInteraction(window_);
        }
    }
}

void Scene::render() {
    for (auto &d: widgets_) {
        assert(d != nullptr);
        window_.draw(*d);
    }
}

void Scene::resize(sf::Vector2f area) {
    window_.setSize(sf::Vector2u(static_cast<unsigned int>(area.x), static_cast<unsigned int>(area.y)));
    window_.setView(sf::View(sf::FloatRect(0, 0, area.x, area.y)));
    win_width_ = area.x;
}
