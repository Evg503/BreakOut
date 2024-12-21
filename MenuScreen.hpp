#pragma once
#include <SFML/Graphics.hpp>

class MenuScreen
{
public:
    MenuScreen(float width, float height)
    {
        if (!font.loadFromFile("fonts/Marker Felt.ttf"))
        {
            // Handle error
            throw std::runtime_error("Failed to load font");
        }

        title.setFont(font);
        title.setString("Breakout Game");
        title.setCharacterSize(70);
        title.setFillColor(sf::Color::White);
        title.setPosition(sf::Vector2f(width / 2 - title.getGlobalBounds().width / 2, height / 4));

        playButton.setFont(font);
        playButton.setString("Play");
        playButton.setCharacterSize(50);
        playButton.setFillColor(sf::Color::White);
        playButton.setPosition(sf::Vector2f(width / 2 - playButton.getGlobalBounds().width / 2, height / 2));

        exitButton.setFont(font);
        exitButton.setString("Exit");
        exitButton.setCharacterSize(50);
        exitButton.setFillColor(sf::Color::White);
        exitButton.setPosition(sf::Vector2f(width / 2 - exitButton.getGlobalBounds().width / 2, height / 2 + 100));
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(title);
        window.draw(playButton);
        window.draw(exitButton);
    }

    bool isPlayButtonPressed(sf::RenderWindow &window)
    {
        return isButtonPressed(window, playButton);
    }

    bool isExitButtonPressed(sf::RenderWindow &window)
    {
        return isButtonPressed(window, exitButton);
    }

private:
    sf::Font font;
    sf::Text title;
    sf::Text playButton;
    sf::Text exitButton;

    bool isButtonPressed(sf::RenderWindow &window, sf::Text &button)
    {
        sf::FloatRect bounds = button.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                return true;
            }
        }
        return false;
    }
};
