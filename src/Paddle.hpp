#pragma once
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "SceneObject.hpp"

class Paddle: public SceneObject
{
public:
    sf::Vector2f velocity;

    Paddle(float x, float y)
    {
        shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{paddleWidth, paddleHeight});
        shape->setPosition(x, y);
        shape->setFillColor(sf::Color::Green);
        shape->setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update(sf::Window &window) override
    {
        shape->move(velocity);
        auto mouseX = static_cast<float>(sf::Mouse::getPosition(window).x);
        shape->setPosition(mouseX, shape->getPosition().y);
    }
};
