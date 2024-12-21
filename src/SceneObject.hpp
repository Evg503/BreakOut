#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>

class SceneObject
{

public:
    SceneObject()
    {
    }
    virtual ~SceneObject() = default;

    virtual void update(sf::Window &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;

    float x() const { return shape->getPosition().x; }
    float y() const { return shape->getPosition().y; }
    float left() const { return shape->getGlobalBounds().left; }
    float right() const { return shape->getGlobalBounds().left + shape->getGlobalBounds().width; }
    float top() const { return shape->getGlobalBounds().top; }
    float bottom() const { return shape->getGlobalBounds().top + shape->getGlobalBounds().height; }
    

    protected:
    std::unique_ptr<sf::Shape> shape;
}