#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"

class Paddle
{
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Paddle(float x, float y)
    {
        shape.setPosition(x, y);
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update(sf::Window &window)
    {
        shape.move(velocity);
        auto mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
        shape.setPosition(mouseX, shape.getPosition().y);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
        //     velocity.x = -paddleVelocity;
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < windowWidth)
        //     velocity.x = paddleVelocity;
        // else
        //     velocity.x = 0;
    }
    void move(float dx, float dy)
    {
        shape.move(dx, dy);
    }
    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getSize().x / 2.f; }
    float right() const { return x() + shape.getSize().x / 2.f; }
    float top() const { return y() - shape.getSize().y / 2.f; }
    float bottom() const { return y() + shape.getSize().y / 2.f; }
};
