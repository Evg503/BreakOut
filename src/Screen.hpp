#pragma once
#ifndef SCREEN_HPP
#define SCREEN_HPP

class Screen {
public:
    virtual ~Screen() = default;

    virtual void update(sf::Window &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

#endif // SCREEN_HPP