#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameScreen.hpp"
#include "config.hpp"
#include "MenuScreen.hpp"

class Application
{
public:
    Application()
        : window{{windowWidth, windowHeight, 1}, "Breakout"/*, sf::Style::Fullscreen*/}
    {
        menuScreen = std::make_unique<MenuScreen>(windowWidth, windowHeight);
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
    std::unique_ptr<GameScreen> gameScreen;
    std::unique_ptr<MenuScreen> menuScreen;

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
        {
            window.close();
        }
        if (gameScreen)
        {
            if(gameScreen->update(window))
            {
                gameScreen.reset();
                menuScreen = std::make_unique<MenuScreen>(windowWidth, windowHeight);
            }
        }
        if (menuScreen)
        {
            if (menuScreen->isPlayButtonPressed(window))
            {
                menuScreen.reset();
                gameScreen = std::make_unique<GameScreen>();
            }
            else if (menuScreen->isExitButtonPressed(window))
            {
                window.close();
            }
        }
    }

    void draw()
    {
        window.clear(sf::Color::Black);
        if (menuScreen)
            menuScreen->draw(window);
        if (gameScreen)
            gameScreen->draw(window);
        window.display();
    }
};
