#pragma once
#include <SFML/Graphics.hpp>


class Screen {
public:
    virtual ~Screen() = default;

    virtual bool update(sf::Window &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

