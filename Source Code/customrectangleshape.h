#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &position, const sf::Color &color, int speed, const sf::RenderWindow &window);
    void animate(const sf::Time &time);
    void handle_mouse_button(const sf::Event &event);

  void step(float time_step);
  void moveInDirection(float elapsed, const sf::Keyboard::Key &key);
  bool isPointedTo(const sf::Vector2i &mouse_position) const;
  void select();
  void deselect();

private:
  sf::Vector2u window_size_;
  float rotation_speed_;
  bool is_currently_selected_ = false;
  const sf::RenderWindow &window_;
  int x_speed_;
  int y_speed_;
  const sf::Color default_color_;
  bool selected_ = false;

  void bounce();
};

