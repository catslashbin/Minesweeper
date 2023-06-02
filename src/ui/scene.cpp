
#include "scene.hpp"

#include <cassert>
#include <utility>

void Scene::changeScene(std::shared_ptr<Scene> target_scene) {
    has_returned = true;
    next_scene = std::move(target_scene);
}

void Scene::render() {
    for (auto &d : drawables_) {
        assert(d != nullptr);
        window_.draw(*d);
    }
}
