#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "config.hpp"


class Ball: public SceneObject
{
public:
    sf::Vector2f velocity{-ballVelocity, -ballVelocity};

    Ball(float x, float y, float radius = ballRadius)
    {
        std::random_device rd;
        gen.seed(rd());
        shape = std::make_unique<sf::CircleShape>(radius);
        shape->setPosition(x, y);
        shape->setFillColor(sf::Color::Red);
        shape->setOrigin(radius, radius);
    }

    bool update()
    {
        shape->move(velocity);

        std::uniform_real_distribution<float> dis(0.8f, 1.2f);

        if (left() < 0 || right() > windowWidth)
            velocity.x = -velocity.x * dis(gen);

        if (top() < 0 || bottom() > windowHeight)
            velocity.y = -velocity.y * dis(gen);

        return false;
    }

public:
    std::mt19937 gen;
};
