#ifndef MINESWEEPER_CLICKABLE_HPP
#define MINESWEEPER_CLICKABLE_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Window/Mouse.hpp>
#include <functional>
#include <memory>
#include <utility>

#define CLICKABLE(T, ...) std::make_shared<Clickable>(std::make_shared<T>(T(__VA_ARGS__)), window_)
#define MAKE_CLICKABLE(S) std::make_shared<Clickable>(S, window_)

class Clickable : public sf::Shape {
private:
    bool last_is_left_clicked_ = false;
    bool last_is_right_clicked_ = false;
    bool last_is_double_clicked_ = false;
    bool last_is_hovering_ = false;

    sf::RenderWindow &window_;
    std::shared_ptr<sf::Shape> m_shape_;

    std::function<void(void)> on_left_click_handler_ = []() {};
    std::function<void(void)> on_right_click_handler_ = []() {};
    std::function<void(void)> on_double_click_handler_ = []() {};
    std::function<void(bool is_hover)> on_hover_change_handler_ = [](bool is_hover) {};

public:
    explicit Clickable(std::shared_ptr<sf::Shape> shape, sf::RenderWindow &window);

    void setOnLeftClickHandler(std::function<void(void)> handler);

    void setOnRightClickHandler(std::function<void(void)> handler);

    void setOnDoubleClickHandler(std::function<void(void)> handler);

    void setOnHoverChangeHandler(std::function<void(bool is_hover)> handler);

    void handleInteraction();

public:
    /* Wrapper functions for virtual functions in Shape */
    std::size_t getPointCount() const override;

    sf::Vector2f getPoint(std::size_t index) const override;
};


#endif //MINESWEEPER_CLICKABLE_HPP
