#pragma once
#include <SFML/Graphics.hpp>

class Block
{
public:
    sf::RectangleShape shape;
    bool destroyed{false};

    Block(float x, float y, float blockWidth, float blockHeight)
    {
        shape.setPosition(x, y);
        shape.setSize({blockWidth, blockHeight});
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getSize().x / 2.f; }
    float right() const { return x() + shape.getSize().x / 2.f; }
    float top() const { return y() - shape.getSize().y / 2.f; }
    float bottom() const { return y() + shape.getSize().y / 2.f; }
};
