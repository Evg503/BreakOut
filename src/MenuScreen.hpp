#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Screen.hpp"
#include "Button.hpp"

class MenuScreen : public Screen
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

        playButton.init(font, "Play", sf::Vector2f(width / 2, height / 2));
        secondButton.init(font, "Secret game", sf::Vector2f(width / 2, height / 2 + 100));
        exitButton.init(font, "Exit", sf::Vector2f(width / 2, height / 2 + 200));
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(title);
        playButton.draw(window);
        secondButton.draw(window);
        exitButton.draw(window);
    }
    bool update(sf::Window &window) override
    {
        playButton.update(window);
        secondButton.update(window);
        exitButton.update(window);
        return false;
    };
    void setPlayButtonPressedCallback(std::function<void()> callback)
    {
        playButton.setOnClick(callback);
    }
    void setSecondButtonPressedCallback(std::function<void()> callback)
    {
        secondButton.setOnClick(callback);
    }
    void setExitButtonPressedCallback(std::function<void()> callback)
    {
        exitButton.setOnClick(callback);
    }

private:
    sf::Font font;
    sf::Text title;
    Button playButton;
    Button secondButton;
    Button exitButton;
    std::vector<Button> buttons;

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
