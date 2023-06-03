
#include "scene.hpp"
#include "clickable.hpp"
#include "consts.hpp"

#include <cassert>
#include <utility>

void Scene::changeScene(std::shared_ptr<Scene> target_scene) {
    debug("Trigger scene change");
    next_scene = std::move(target_scene);
}

void Scene::registerWidget(const std::shared_ptr<sf::Drawable>& widget) {
    widgets_.push_back(widget);
}

void Scene::handleInteractions() {
    for (const auto &d: widgets_) {
        if (auto c = dynamic_cast<Clickable *>(d.get())) {
            c->handleInteraction();
        }
    }
}

void Scene::render() {
    for (auto &d: widgets_) {
        assert(d != nullptr);
        window_.draw(*d);
    }
}
