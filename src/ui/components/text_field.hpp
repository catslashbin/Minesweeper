#ifndef MINESWEEPER_TEXT_FIELD_HPP
#define MINESWEEPER_TEXT_FIELD_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Window/Event.hpp>

namespace sf {
    class TextField : public sf::Transformable, public sf::Drawable {
    private:
        unsigned int m_size_;
        sf::Font m_font_;
        std::string m_text_;
        sf::RectangleShape m_rect_;
        bool m_hasfocus_;

    public:
        TextField(unsigned int maxChars, sf::Font &font);
        std::string getText() const;
        void draw(RenderTarget &target, RenderStates states) const override;
        void setPosition(float x, float y);
        bool contains(Vector2f point) const;
        void setFocus(bool focus);
        void handleInput(sf::Event e);
    };
} // namespace sf

#endif //MINESWEEPER_TEXT_FIELD_HPP
