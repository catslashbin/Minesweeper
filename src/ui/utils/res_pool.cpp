#include "res_pool.hpp"
#include "consts.hpp"

std::map<std::string, std::shared_ptr<sf::Texture>> ResPool::textures_;
std::map<std::string, std::shared_ptr<sf::Font>> ResPool::fonts_;

std::shared_ptr<sf::Texture> ResPool::getTexture(const std::string &path) {
    auto it = textures_.find(path);
    if (it == textures_.end()) {
        auto texture = std::make_shared<sf::Texture>();
        if (texture->loadFromFile(ASSETS_DIR + path)) {
            texture->setSmooth(true);
            textures_[path] = texture;
            debug("Texture loaded: {}", path);
            return texture;
        }
        warn("Texture not found: {}", path);
        return nullptr;
    }
    return it->second;
}

std::shared_ptr<sf::Font> ResPool::getFont(const std::string &path) {
    auto it = fonts_.find(path);
    if (it == fonts_.end()) {
        auto font = std::make_shared<sf::Font>();
        if (font->loadFromFile(ASSETS_DIR + path)) {
            fonts_[path] = font;
            debug("Font loaded: {}", path);
            return font;
        }
        warn("Font not found: {}", path);
        return nullptr;
    }
    return it->second;
}
