#include "res_pool.hpp"
#include "ui/consts.hpp"

ResPool &ResPool::getInstance() {
    static ResPool instance;
    return instance;
}
std::shared_ptr<sf::Texture> ResPool::getTexture(const std::string &path) {
    auto it = textures_.find(ASSETS_DIR + path);
    if (it == textures_.end()) {
        auto texture = std::make_shared<sf::Texture>();
        if (texture->loadFromFile(ASSETS_DIR + path)) {
            textures_[path] = texture;
            return texture;
        }
        return nullptr;
    }
    return it->second;
}
std::shared_ptr<sf::Font> ResPool::getFont(const std::string &path) {
    auto it = fonts_.find(ASSETS_DIR + path);
    if (it == fonts_.end()) {
        auto font = std::make_shared<sf::Font>();
        if (font->loadFromFile(ASSETS_DIR + path)) {
            fonts_[path] = font;
            return font;
        }
        return nullptr;
    }
    return it->second;
}
