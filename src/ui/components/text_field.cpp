#include "text_field.hpp"

namespace sf {
    TextField::TextField(unsigned int maxChars, sf::Font &font) : m_size_(maxChars),
                                                                  m_rect_(sf::Vector2f(static_cast<float>(15 * m_size_), 20)),
                                                                  m_hasfocus_(false) {
        m_font_ = font;
        m_rect_.setOutlineThickness(2);
        m_rect_.setFillColor(sf::Color::White);
        m_rect_.setOutlineColor(sf::Color(127, 127, 127));
        m_rect_.setPosition(this->getPosition());
    }

    std::string sf::TextField::getText() const {
        return m_text_;
    }

    void sf::TextField::setPosition(float x, float y) {
        sf::Transformable::setPosition(x, y);
        m_rect_.setPosition(x, y);
    }

    bool sf::TextField::contains(sf::Vector2f point) const {
        return m_rect_.getGlobalBounds().contains(point);
    }

    void sf::TextField::setFocus(bool focus) {
        m_hasfocus_ = focus;
        if (focus) {
            m_rect_.setOutlineColor(sf::Color::Blue);
        } else {
            m_rect_.setOutlineColor(sf::Color(127, 127, 127)); // Gray color
        }
    }

    void sf::TextField::handleInput(sf::Event e) {
        if (!m_hasfocus_ || e.type != sf::Event::TextEntered)
            return;

        if (e.text.unicode == 8) { // Delete key
            m_text_ = m_text_.substr(0, m_text_.size() - 1);
        } else if (m_text_.size() < m_size_) {
            m_text_ += std::to_string(e.text.unicode);
        }
    }
    void sf::TextField::draw(RenderTarget &target, RenderStates states) const {
    }

} // namespace sf