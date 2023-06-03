
#include "scene.hpp"
#include "consts.hpp"
#include "ui/utils/clickable.hpp"

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

/// \n It can be used like: \n
/// resize(visibleArea(0, 0, static_cast\<float\>(90 DP), static_cast\<float\>(120 DP)));
void Scene::resize(sf::FloatRect area) {
    window_.setSize(sf::Vector2u(static_cast<unsigned int>(area.width),
                                 static_cast<unsigned int>(area.height)));
    window_.setView(sf::View(area));
    win_width_ = area.width;
}
