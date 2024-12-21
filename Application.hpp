#pragma once
#include <SFML/Graphics.hpp>
#include "GameScreen.hpp"
#include "config.hpp"

class Application
{
public:
    Application()
        : window{{windowWidth, windowHeight}, "Breakout"}
    {
        window.setFramerateLimit(60);
    }

    void run()
    {
        while (window.isOpen())
        {
            processEvents();
            update();
            draw();
        }
    }

private:
    sf::RenderWindow window;
    GameScreen gameScreen;
    void processEvents()
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

    void update()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

        gameScreen.update();
    }

    void draw()
    {
        window.clear(sf::Color::Black);
        gameScreen.draw(window);
        window.display();
    }
};
