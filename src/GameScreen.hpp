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
        {
            for (int iY{0}; iY < blockRows; ++iY)
            {

                blocks.emplace_back(startBlocksX + iX * blockWidth, startBlocksY + iY * blockHeight, blockWidth - 1, blockHeight - 1);
            }
        }
    }

    bool update(sf::Window &window)
    {
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && emitClock.getElapsedTime().asSeconds() >= 0.1f)
        {
            balls.emplace_back(paddle.x(), paddle.top());
            emitClock.restart();
        }

        for (auto &ball : balls)
        {
            ball.update(window);
        }
        paddle.update(window);
        for (auto &ball : balls)
        {
            testCollision(paddle, ball);
        }
        for (auto &ball : balls)
        {
            for (auto &block : blocks)
                if (testCollision(block, ball))
                    break; //next ball
            ;
        }
        blocks.erase(std::remove_if(begin(blocks), end(blocks), [](const Block &mBlock)
                                    { return mBlock.destroyed; }),
                     end(blocks));

        if (!gameOver && blocks.empty())
        {
            finalCountDownClock.restart();
            gameOver = true;
        }
        return gameOver && finalCountDownClock.getElapsedTime().asSeconds() >= 3.f;
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &ball : balls)
        {
            ball.draw(window);
        }
        paddle.draw(window);
        for (auto &block : blocks)
            block.draw(window);
    }

private:
    Paddle paddle;
    std::vector<Ball> balls;
    std::vector<Block> blocks;
    bool gameOver{false};
    sf::Clock emitClock;
    sf::Clock finalCountDownClock;
};
