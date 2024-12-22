#pragma once
#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <vector>
#include "SFML/Graphics.hpp"
#include "Screen.hpp"

class Asteroid
{
public:
    Asteroid(sf::Vector2f position, sf::Vector2f velocity, float radius);
    // Copy constructor
    Asteroid(const Asteroid &other)
    {
        position = other.position;
        rotation = other.rotation;
        velocity = other.velocity;
        rotationSpeed = other.rotationSpeed;
        radius = other.radius;

        texture = other.texture;
        sprite = other.sprite;
        sprite.setTexture(texture);
    }

    // Move constructor
    Asteroid(Asteroid &&other) noexcept
    {
        position = other.position;
        rotation = other.rotation;
        velocity = other.velocity;
        rotationSpeed = other.rotationSpeed;
        radius = other.radius;

        texture.swap(other.texture);
        sprite = other.sprite;
        // sprite.setTexture(texture);//? may be not needed
    }

    // Copy assignment operator
    Asteroid &operator=(const Asteroid &other)
    {
        if (this != &other)
        {
            position = other.position;
            rotation = other.rotation;
            velocity = other.velocity;
            rotationSpeed = other.rotationSpeed;
            radius = other.radius;
            sf::Texture temp = sf::Texture(other.texture);
            texture.swap(temp);
            sprite = other.sprite;
            sprite.setTexture(texture);
        }
        return *this;
    }

    // Move assignment operator
    Asteroid &operator=(Asteroid &&other) noexcept
    {
        if (this != &other)
        {
            position = other.position;
            rotation = other.rotation;
            velocity = other.velocity;
            rotationSpeed = other.rotationSpeed;
            radius = other.radius;

            texture.swap(other.texture);
            sprite = other.sprite;
            sprite.setTexture(texture);
        }
        return *this;
    }

    // Destructor
    ~Asteroid() {}

    void update(float deltaTime);
    void draw(sf::RenderWindow &window) const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getGlobalBounds() const;
    float getRadius() const;

private:
    sf::Vector2f position;
    float rotation;
    sf::Vector2f velocity;
    float rotationSpeed;
    float radius;
    sf::Sprite sprite;
    sf::Texture texture; // Hold the texture
};

class AsteroidsGameScreen : public Screen
{
public:
    AsteroidsGameScreen();
    bool update(sf::Window &window) override;
    void draw(sf::RenderWindow &window) override;
    void addAsteroid(const Asteroid &asteroid);

private:
    std::vector<Asteroid> asteroids;
};

#endif // ASTEROIDS_H