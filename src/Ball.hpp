#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "config.hpp"


class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity{-ballVelocity, -ballVelocity};

    Ball(float x, float y, float radius = ballRadius)
    {
        std::random_device rd;
        gen.seed(rd());
        shape.setPosition(x, y);
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(radius, radius);
    }

    void update()
    {
        shape.move(velocity);

        std::uniform_real_distribution<float> dis(0.8f, 1.2f);

        if (left() < 0 || right() > windowWidth)
            velocity.x = -velocity.x * dis(gen);

        if (top() < 0 || bottom() > windowHeight)
            velocity.y = -velocity.y * dis(gen);
    }
    void move(float dx, float dy)
    {
        shape.move(dx, dy);
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getRadius(); }
    float right() const { return x() + shape.getRadius(); }
    float top() const { return y() - shape.getRadius(); }
    float bottom() const { return y() + shape.getRadius(); }

public:
    std::mt19937 gen;
};
