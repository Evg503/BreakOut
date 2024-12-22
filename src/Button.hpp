#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

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
        // TODO: window.draw(back);
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
                    if (onClick)
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
    // TODO: sf::RectangleShape back;
    sf::Text text;
    std::function<void()> onClick;
    State state{State::Normal};

private:
    Style normalStyle{sf::Color::White, 50};
    Style hoverStyle{sf::Color::Yellow, 52};
    Style pressedStyle{sf::Color::Green, 55};
};
