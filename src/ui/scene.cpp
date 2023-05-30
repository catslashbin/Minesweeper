
#include "scene.hpp"

#include <utility>

void Scene::changeScene(std::shared_ptr<Scene> target_scene) {
    has_returned = true;
    next_scene = std::move(target_scene);
}
