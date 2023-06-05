#include "clickable.hpp"

#include <cassert>
#include <ui/utils/consts.hpp>
#include <utility>

void Clickable::setOnLeftClickHandler(std::function<void(void)> handler) {
    on_left_click_handler_ = std::move(handler);
}

void Clickable::setOnRightClickHandler(std::function<void(void)> handler) {
    on_right_click_handler_ = std::move(handler);
}

void Clickable::setOnDoubleClickHandler(std::function<void(void)> handler) {
    on_double_click_handler_ = std::move(handler);
}

void Clickable::setOnHoverChangeHandler(std::function<void(bool)> handler) {
    on_hover_change_handler_ = std::move(handler);
}

void Clickable::handleInteraction(sf::RenderWindow &window) {
    sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

    assert(dynamic_cast<sf::Shape *>(this) != nullptr);
    bool in_bound = dynamic_cast<sf::Shape *>(this)->getGlobalBounds().contains(
            float(mouse_position.x), float(mouse_position.y));

    bool is_left_click = in_bound && sf::Mouse::isButtonPressed(sf::Mouse::Left);
    bool is_right_click = in_bound && sf::Mouse::isButtonPressed(sf::Mouse::Right);

    // Handle hover change
    if (last_is_hovering_ != in_bound)
        on_hover_change_handler_(in_bound);

    // Handle left click
    if (last_is_left_clicked_ && !is_left_click) {
        debug("Elapsed time: {}", last_left_click_time_.getElapsedTime().asMilliseconds());
        if (last_left_click_time_.getElapsedTime().asMilliseconds() < EPS_DOUBLE_CLICK) {
            on_double_click_handler_();
        } else {
            on_left_click_handler_();
        }
        last_left_click_time_.restart();
    }

    // if (in_bound) {
    //     debug("left: {}, right: {}", is_right_click, is_left_click);
    // }

    // Handle right click
    if (last_is_right_clicked_ && !is_right_click)
        on_right_click_handler_();

    last_is_hovering_ = in_bound;
    last_is_left_clicked_ = is_left_click;
    last_is_right_clicked_ = is_right_click;
}
