#pragma once
#include <SFML/Graphics.hpp>

class Block: public SceneObject
{
public:
    bool destroyed{false};

    Block(float x, float y, float blockWidth, float blockHeight)
    {
        shape = std::make_unique<sf::RectangleShape>(sf::Vector2f{blockWidth, blockHeight});
        shape->setPosition(x, y);
        shape->setFillColor(sf::Color::Yellow);
        shape->setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }
    Block(Block const &) = delete;
    Block &operator=(Block const &) = delete;
    Block(Block &&) = default;
    Block &operator=(Block &&) = default;

};
