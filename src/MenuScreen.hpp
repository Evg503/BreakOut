#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Screen.hpp"
#include <iostream>
class Style
{
public:
    Style(const sf::Color &color, int characterSize) : color{color}, characterSize{characterSize}
    {
    }
    void apply(sf::Text &text)
    {
        text.setFillColor(color);
        text.setCharacterSize(characterSize);
    }

private:
    sf::Color color;
    int characterSize;
};
enum class State
{
    Normal,
    Hover,
    Pressed
};
class Button
{
public:
    Button() = default;
    void init(const sf::Font &font, const std::string &title, const sf::Vector2f &position)
    {
        text.setFont(font);
        text.setString(title);
        text.setPosition(position);
        auto textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        
        normalStyle.apply(text);
    }

    void draw(sf::RenderWindow &window)
    {
        //TODO: window.draw(back);
        window.draw(text);
    }
    sf::FloatRect getGlobalBounds()
    {
        return text.getGlobalBounds();
    }
    void setOnClick(std::function<void()> onClick)
    {
        this->onClick = onClick;
    }
    void update(sf::Window &window)
    {
        State newState{state};
        switch (state)
        {
        case State::Normal:
            if (isHovered(window))
            {
                newState = State::Hover;
                if (isPressed(window))
                {
                    newState = State::Pressed;
                }
            }
            else
            {
                newState = State::Normal;
            }
            break;
        case State::Hover:
            if (!isHovered(window))
            {
                newState = State::Normal;
            }
            else if (isPressed(window))
            {
                newState = State::Pressed;
            }
            break;
        case State::Pressed:
            if (!isPressed(window))
            {
                if (isHovered(window))
                {
                    newState = State::Hover;
                    onClick();
                }
                else
                {
                    newState = State::Normal;
                }
            }
            break;
        };
        if (newState != state)
        {
            state = newState;
            switch (state)
            {
            case State::Normal:
                normalStyle.apply(text);
                break;
            case State::Hover:
                hoverStyle.apply(text);
                break;
            case State::Pressed:
                pressedStyle.apply(text);
                break;
            }
        }
    }
    bool isHovered(sf::Window &window)
    {
        sf::FloatRect bounds = text.getGlobalBounds();
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
        {
            return true;
        }
        return false;
    }
    bool isPressed(sf::Window &window)
    {
        sf::FloatRect bounds = text.getGlobalBounds();
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

private:
    //TODO: sf::RectangleShape back;
    sf::Text text;
    std::function<void()> onClick;
    State state{State::Normal};

private:
    Style normalStyle{sf::Color::White, 50};
    Style hoverStyle{sf::Color::Yellow, 52};
    Style pressedStyle{sf::Color::Green, 55};
};
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

        playButton.init(font, "Play", sf::Vector2f(width / 2 , height / 2));
        exitButton.init(font, "Exit", sf::Vector2f(width / 2 , height / 2+100));

        playButton.setOnClick([this]() {
            isPlayPressed = true;
        });
        exitButton.setOnClick([this]() {
            isExitPressed = true;
        });
    }

    void draw(sf::RenderWindow &window) override
    {
        window.draw(title);
        playButton.draw(window);
        exitButton.draw(window);
    }
    void update(sf::Window &window) override {
        playButton.update(window);
        exitButton.update(window);  
    };

    bool isPlayButtonPressed(sf::RenderWindow &window)
    {
        bool returnValue = isPlayPressed;
        isPlayPressed = false;
        return returnValue;
    }

    bool isExitButtonPressed(sf::RenderWindow &window)
    {
        bool returnValue = isExitPressed;
        isExitPressed = false;
        return returnValue;
    }

private:
    sf::Font font;
    sf::Text title;
    Button playButton;
    Button exitButton;
    std::vector<Button> buttons;
    bool isPlayPressed{false};
    bool isExitPressed{false};

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
