#include "button.hpp"

Button::Button(const sf::Texture &texture, sf::RenderWindow &window) : sf::Sprite(texture), window_(window) {}

void Button::setOnLeftClickHandler(std::function<void(void)> handler) {
    on_left_click_handler_ = std::move(handler);
}

void Button::setOnRightClickHandler(std::function<void(void)> handler) {
    on_right_click_handler_ = std::move(handler);
}

void Button::setOnDoubleClickHandler(std::function<void(void)> handler) {
    on_double_click_handler_ = std::move(handler);
}

void Button::setOnHoverChangeHandler(std::function<void(bool)> handler) {
    on_hover_change_handler_ = std::move(handler);
}

void Button::update() {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window_);

    bool in_bound = getGlobalBounds().contains(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y));
    bool is_left_click = in_bound && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool is_right_click = in_bound && sf::Mouse::isButtonPressed(sf::Mouse::Right);
    bool is_double_click = is_left_click && is_right_click;

    // Handle hover change
    if (last_is_hovering_ != in_bound)
        on_hover_change_handler_(in_bound);

    // Handle double click
    if (last_is_double_clicked_ && !is_double_click) {

        // Skip left & right handler
        on_left_click_handler_();

    } else {

        // Handle left click
        if (last_is_left_clicked_ && !is_left_click)
            on_left_click_handler_();

        // Handle right click
        if (last_is_right_clicked_ && !is_right_click)
            on_left_click_handler_();
    }

    last_is_hovering_ = in_bound;
    last_is_left_clicked_ = is_left_click;
    last_is_right_clicked_ = is_right_click;
    last_is_double_clicked_ = is_double_click;
}
