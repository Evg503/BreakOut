#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Constants
const int windowWidth = 800;
const int windowHeight = 600;
const float ballRadius = 10.f;
const float ballVelocity = 8.f;
const float paddleWidth = 60.f;
const float paddleHeight = 20.f;
const float paddleVelocity = 6.f;
const int blockRows = 15;
const int blockColumns = 51;
const int initialBallCount = 3;
// Ball class
class Ball
{
public:
    sf::CircleShape shape;
    sf::Vector2f velocity{-ballVelocity, -ballVelocity};

    Ball(float x, float y)
    {
        shape.setPosition(x, y);
        shape.setRadius(ballRadius);
        shape.setFillColor(sf::Color::Red);
        shape.setOrigin(ballRadius, ballRadius);
    }

    void update()
    {
        shape.move(velocity);

        if (left() < 0)
            velocity.x = ballVelocity;
        else if (right() > windowWidth)
            velocity.x = -ballVelocity;

        if (top() < 0)
            velocity.y = ballVelocity;
        else if (bottom() > windowHeight)
            velocity.y = -ballVelocity;
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getRadius(); }
    float right() const { return x() + shape.getRadius(); }
    float top() const { return y() - shape.getRadius(); }
    float bottom() const { return y() + shape.getRadius(); }
};

// Paddle class
class Paddle
{
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    Paddle(float x, float y)
    {
        shape.setPosition(x, y);
        shape.setSize({paddleWidth, paddleHeight});
        shape.setFillColor(sf::Color::Green);
        shape.setOrigin(paddleWidth / 2.f, paddleHeight / 2.f);
    }

    void update()
    {
        shape.move(velocity);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && left() > 0)
            velocity.x = -paddleVelocity;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && right() < windowWidth)
            velocity.x = paddleVelocity;
        else
            velocity.x = 0;
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getSize().x / 2.f; }
    float right() const { return x() + shape.getSize().x / 2.f; }
    float top() const { return y() - shape.getSize().y / 2.f; }
    float bottom() const { return y() + shape.getSize().y / 2.f; }
};

// Block class
class Block
{
public:
    sf::RectangleShape shape;
    bool destroyed{false};

    Block(float x, float y, float blockWidth, float blockHeight)
    {
        shape.setPosition(x, y);
        shape.setSize({blockWidth, blockHeight});
        shape.setFillColor(sf::Color::Yellow);
        shape.setOrigin(blockWidth / 2.f, blockHeight / 2.f);
    }

    float x() const { return shape.getPosition().x; }
    float y() const { return shape.getPosition().y; }
    float left() const { return x() - shape.getSize().x / 2.f; }
    float right() const { return x() + shape.getSize().x / 2.f; }
    float top() const { return y() - shape.getSize().y / 2.f; }
    float bottom() const { return y() + shape.getSize().y / 2.f; }
};

// Collision detection
template <class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

void testCollision(Paddle &mPaddle, Ball &mBall)
{
    if (!isIntersecting(mPaddle, mBall))
        return;

    mBall.velocity.y = -ballVelocity;

    if (mBall.x() < mPaddle.x())
        mBall.velocity.x = -ballVelocity;
    else
        mBall.velocity.x = ballVelocity;
}

void testCollision(Block &mBlock, Ball &mBall)
{
    if (!isIntersecting(mBlock, mBall))
        return;

    mBlock.destroyed = true;

    float overlapLeft{mBall.right() - mBlock.left()};
    float overlapRight{mBlock.right() - mBall.left()};
    float overlapTop{mBall.bottom() - mBlock.top()};
    float overlapBottom{mBlock.bottom() - mBall.top()};

    bool ballFromLeft(std::abs(overlapLeft) < std::abs(overlapRight));
    bool ballFromTop(std::abs(overlapTop) < std::abs(overlapBottom));

    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};

    if (std::abs(minOverlapX) < std::abs(minOverlapY))
        mBall.velocity.x = ballFromLeft ? -ballVelocity : ballVelocity;
    else
        mBall.velocity.y = ballFromTop ? -ballVelocity : ballVelocity;
}

class Application
{
public:
    Application()
        : window{{windowWidth, windowHeight}, "Breakout"},
          paddle{windowWidth / 2, windowHeight - 50}
    {
        window.setFramerateLimit(60);

        float startBlocksX{0.1*windowWidth};
        float endBlocksX{0.9*windowWidth};
        float startBlocksY{0.1*windowHeight};
        float endBlocksY{0.5*windowHeight};
        float blockHeight{(endBlocksY-startBlocksY)/blockRows};
        float blockWidth{(endBlocksX-startBlocksX)/blockColumns};
        for (int iX{0}; iX < blockColumns; ++iX)
            for (int iY{0}; iY < blockRows; ++iY)
                blocks.emplace_back(startBlocksX + iX*blockWidth, startBlocksY + iY*blockHeight, blockWidth-1, blockHeight-1);
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
    std::vector<Ball> balls;
    Paddle paddle;
    std::vector<Block> blocks;

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
        static sf::Clock clock;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && clock.getElapsedTime().asSeconds() >= 0.1f)
        {
            balls.emplace_back(paddle.x(), paddle.top());
            clock.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            window.close();

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

    void draw()
    {
        window.clear(sf::Color::Black);

        for (auto &ball : balls)
        {
            window.draw(ball.shape);
        }
        window.draw(paddle.shape);
        for (auto &block : blocks)
            window.draw(block.shape);

        window.display();
    }
};

int main()
{
    Application app;
    app.run();
    return 0;
}
