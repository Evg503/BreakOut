#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "config.hpp"
#include "Collision.hpp"

class GameScreen
{
public:
    GameScreen()
        : paddle{windowWidth / 2, windowHeight - 50}
    {
        float startBlocksX{0.1 * windowWidth};
        float endBlocksX{0.9 * windowWidth};
        float startBlocksY{0.1 * windowHeight};
        float endBlocksY{0.5 * windowHeight};
        float blockHeight{(endBlocksY - startBlocksY) / blockRows};
        float blockWidth{(endBlocksX - startBlocksX) / blockColumns};
        for (int iX{0}; iX < blockColumns; ++iX)
            for (int iY{0}; iY < blockRows; ++iY)
                blocks.emplace_back(startBlocksX + iX * blockWidth, startBlocksY + iY * blockHeight, blockWidth - 1, blockHeight - 1);
    }

    void update()
    {
        static sf::Clock clock;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && clock.getElapsedTime().asSeconds() >= 0.1f)
        {
            balls.emplace_back(paddle.x(), paddle.top());
            clock.restart();
        }

        for (auto &ball : balls)
        {
            ball.update();
        }
        paddle.update();
        for (auto &ball : balls)
        {
            testCollision(paddle, ball);
        }
        for (auto &ball : balls)
        {
            for (auto &block : blocks)
                testCollision(block, ball);
        }
        blocks.erase(std::remove_if(begin(blocks), end(blocks), [](const Block &mBlock)
                                    { return mBlock.destroyed; }),
                     end(blocks));
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &ball : balls)
        {
            window.draw(ball.shape);
        }
        window.draw(paddle.shape);
        for (auto &block : blocks)
            window.draw(block.shape);
    }

private:
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<Block> blocks;
};
