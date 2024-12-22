#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameScreen.hpp"
#include "config.hpp"
#include "MenuScreen.hpp"
#include "Asteroids.h"

class Application
{
public:
    Application()
        : window{{windowWidth, windowHeight, 1}, "Breakout"/*, sf::Style::Fullscreen*/}
    {
        menuScreen = std::make_unique<MenuScreen>(windowWidth, windowHeight);
        static_cast<MenuScreen*>(menuScreen.get())->setPlayButtonPressedCallback([this]() {
            gameScreen = std::make_unique<GameScreen>();
        });
        static_cast<MenuScreen*>(menuScreen.get())->setSecondButtonPressedCallback([this]() {
            gameScreen = std::make_unique<AsteroidsGameScreen>();
        });
        static_cast<MenuScreen*>(menuScreen.get())->setExitButtonPressedCallback([this]() {
            window.close();
        });

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
    std::unique_ptr<Screen> gameScreen;
    std::unique_ptr<Screen> menuScreen;

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
            }
        } else
        if (menuScreen)
        {
            menuScreen->update(window);
        }
    }

    void draw()
    {
        window.clear(sf::Color::Black);
        if (gameScreen)
            gameScreen->draw(window);
        else if (menuScreen)
            menuScreen->draw(window);
        window.display();
    }
};
