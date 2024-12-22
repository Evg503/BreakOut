#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "config.hpp"

class Ball : public SceneObject
{
public:
    sf::Vector2f velocity{-ballVelocity, -ballVelocity};
    float radius{ballRadius};

    Ball(float x, float y, float radius = ballRadius):
        radius{radius}
    {
        std::random_device rd;
        gen.seed(rd());
        shape = std::make_unique<sf::CircleShape>(radius);
        shape->setPosition(x, y);
        shape->setFillColor(sf::Color::Red);
        shape->setOrigin(radius, radius);
    }

    void update(sf::Window &window) override
    {
        shape->move(velocity);

        std::uniform_real_distribution<float> dis(1.f, 1.2f);

        if (left() < 0)
        {
            velocity.x = std::min(std::abs(velocity.x * dis(gen)), maxballVelocity);
            shape->setPosition(x() - left(), shape->getPosition().y);
        }
        else if (right() > windowWidth)
        {
            velocity.x = -std::min(std::abs(velocity.x * dis(gen)), maxballVelocity);
            shape->setPosition(windowWidth - (right() - windowWidth) - radius, shape->getPosition().y);
        }

        if (top() < 0)
        {
            velocity.y = std::min(std::abs(velocity.y * dis(gen)), maxballVelocity);
            shape->setPosition(shape->getPosition().x, y() - top());
        }
        else if (bottom() > windowHeight)
        {
            velocity.y = -std::min(std::abs(velocity.y * dis(gen)), maxballVelocity);
            shape->setPosition(shape->getPosition().x, windowHeight - (bottom() - windowHeight) - radius);
        }
    }

public:
    std::mt19937 gen;
};
