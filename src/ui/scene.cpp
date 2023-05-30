
#include "scene.hpp"

#include <utility>

void Scene::changeScene(std::shared_ptr<Intent> intent) {
    return_intent = std::move(intent);
}
