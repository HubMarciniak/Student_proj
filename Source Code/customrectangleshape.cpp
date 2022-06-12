#include "customrectangleshape.h"

CustomRectangleShape::CustomRectangleShape(const sf::Vector2f &position, const sf::Color &color, int speed,
                                           const sf::RenderWindow &window)
    : sf::RectangleShape(sf::Vector2f(120.0, 60.0)), window_(window), x_speed_(speed),
      y_speed_(speed) {
    setPosition(position);
    setFillColor(color);
}

void CustomRectangleShape::animate(const sf::Time &time) {
    float seconds = time.asSeconds();

    bounce();

    if (selected_) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            move(0, -std::abs(y_speed_) * seconds);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            move(0, std::abs(y_speed_) * seconds);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            move(-std::abs(x_speed_) * seconds, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            move(std::abs(x_speed_) * seconds, 0);
        }
    }
    else {
        move(x_speed_ * seconds, y_speed_ * seconds);
        rotate(15 * seconds);
    }
}

void CustomRectangleShape::handle_mouse_button(const sf::Event &event) {
    auto bounding_box = getGlobalBounds();
    if (bounding_box.contains(event.mouseButton.x, event.mouseButton.y)) {
        selected_ = not selected_;
        if (selected_) {
            setFillColor({255, 0, 0});
        }
        else {
            setFillColor(default_color_);
        }
    }
}

void CustomRectangleShape::bounce() {
    sf::FloatRect bounding_box = getGlobalBounds();

    if (bounding_box.left <= 0) {
        x_speed_ = std::abs(x_speed_);
    }
    else if (bounding_box.left + bounding_box.width >= window_.getSize().x) {
        x_speed_ = -std::abs(x_speed_);
    }

    if (bounding_box.top <= 0) {
        y_speed_ = std::abs(y_speed_);
    }
    else if (bounding_box.top + bounding_box.height >= window_.getSize().y) {
        y_speed_ = -std::abs(y_speed_);
    }
}
