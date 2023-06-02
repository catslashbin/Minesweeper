#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>

class ResPool {
public:
    static ResPool &getInstance();

    std::shared_ptr<sf::Texture> getTexture(const std::string &path);

    std::shared_ptr<sf::Font> getFont(const std::string &path);

private:
    ResPool() {}
    ResPool(const ResPool &) = delete;
    ResPool &operator=(const ResPool &) = delete;

    std::map<std::string, std::shared_ptr<sf::Texture>> textures_;
    std::map<std::string, std::shared_ptr<sf::Font>> fonts_;
};
