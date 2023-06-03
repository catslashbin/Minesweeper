
#ifndef MINESWEEPER_RES_POOL_HPP
#define MINESWEEPER_RES_POOL_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

class ResPool {
private:
    static std::map<std::string, std::shared_ptr<sf::Texture>> textures_;
    static std::map<std::string, std::shared_ptr<sf::Font>> fonts_;

public:
    static std::shared_ptr<sf::Texture> getTexture(const std::string &path);

    static std::shared_ptr<sf::Font> getFont(const std::string &path);

    ResPool() = delete;
    ResPool(const ResPool &) = delete;
    ResPool &operator=(const ResPool &) = delete;
};

#endif