#ifndef MINESWEEPER_CLICKABLE_HPP
#define MINESWEEPER_CLICKABLE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <memory>
#include <utility>

#define CLICKABLE(T, ...) std::make_shared<ClickableShape<T>>(__VA_ARGS__)

class Clickable {
private:
    bool last_is_left_clicked_ = false;
    bool last_is_right_clicked_ = false;
    bool last_is_double_clicked_ = false;
    bool last_is_hovering_ = false;

    std::function<void(void)> on_left_click_handler_ = []() {};
    std::function<void(void)> on_right_click_handler_ = []() {};
    std::function<void(void)> on_double_click_handler_ = []() {};
    std::function<void(bool is_hover)> on_hover_change_handler_ = [](bool is_hover) {};

public:
    explicit Clickable() = default;

    virtual ~Clickable() = default;

    void setOnLeftClickHandler(std::function<void(void)> handler);

    void setOnRightClickHandler(std::function<void(void)> handler);

    void setOnDoubleClickHandler(std::function<void(void)> handler);

    void setOnHoverChangeHandler(std::function<void(bool is_hover)> handler);

    void handleInteraction(sf::RenderWindow& window);
};

template<class T>
class ClickableShape : public T, public Clickable {
    using T::T;
};


#endif //MINESWEEPER_CLICKABLE_HPP
