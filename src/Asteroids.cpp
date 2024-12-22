#include "Asteroids.h"
#include "config.hpp"
#include <random>

AsteroidsGameScreen::AsteroidsGameScreen()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0.0f, static_cast<float>(windowWidth));
    std::uniform_real_distribution<float> disY(0.0f, static_cast<float>(windowHeight));
    std::uniform_real_distribution<float> disV(20.0f, 50.0f);
    std::uniform_int_distribution<> disSign(0, 1);
    std::uniform_real_distribution<float> disR(10.0f, 20.0f);
    asteroids.reserve(numAsteroids);
    for (int i = 0; i < numAsteroids; ++i)
    {

        float x = disX(gen);
        float y = disY(gen);
        float vx = disV(gen) * (disSign(gen) * 2 - 1);
        float vy = disV(gen) * (disSign(gen) * 2 - 1);
        float radius = disR(gen);
        asteroids.emplace_back(sf::Vector2f(x, y), sf::Vector2f(vx, vy), radius);
    }
}

bool AsteroidsGameScreen::update(sf::Window &window)
{
    // Update logic
    for (auto &asteroid : asteroids)
    {
        asteroid.update(1.0f / 60.0f); // Assuming 60 FPS
    }
    sf::FloatRect screen = {0, 0, windowWidth, windowHeight};
    asteroids.erase(std::remove_if(begin(asteroids), end(asteroids), [&](const Asteroid &asteroid)
                                   {
                                    auto bounds = asteroid.getGlobalBounds(); 
                                    return !bounds.intersects(screen); }),
                    end(asteroids));
    return asteroids.empty();
}

void AsteroidsGameScreen::draw(sf::RenderWindow &window)
{
    // Rendering code
    for (const auto &asteroid : asteroids)
    {
        asteroid.draw(window);
    }
}

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f velocity, float radius)
    : position(position), velocity(velocity), radius(radius), rotation(0.0f)
{
    // Load texture and set up sprite
    if (!texture.loadFromFile("res/asteroid.png"))
    {
        // Handle loading error
        throw std::runtime_error("Failed to load asteroid texture");
    }
    sprite.setTexture(texture);
    // sprite,setTextureRect(sf::IntRect(0, 0, 320, 240 )); // Assuming the texture is 100x100
    // sprite.setScale(radius / 100.0f, radius / 100.0f); // Assuming the texture is 100x100
    sprite.setOrigin(radius, radius); // Assuming the origin is at the center
}

// Assuming you have a sprite or shape to represent the asteroid
void Asteroid::update(float deltaTime)
{
    // Update position based on velocity and deltaTime
    position += velocity * deltaTime;
    rotation += rotationSpeed * deltaTime; // Assuming you have a rotationSpeed variable

    // Update sprite position and rotation
    sprite.setPosition(position);
    sprite.setRotation(rotation);
}

void Asteroid::draw(sf::RenderWindow &window) const
{
    // Assuming you have a sprite or shape to represent the asteroid
    window.draw(sprite);
}

sf::Vector2f Asteroid::getPosition() const
{
    return sprite.getPosition();
}

sf::FloatRect Asteroid::getGlobalBounds() const
{
    return sprite.getGlobalBounds();
}
