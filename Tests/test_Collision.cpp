#include <gtest/gtest.h>
#include "Collision.hpp"
#include "SceneObject.hpp"

class MockRectangle : public SceneObject
{
private:
    /* data */
public:
    MockRectangle(float x, float y, float width, float height)
    {
        shape = std::make_unique<sf::RectangleShape>(sf::Vector2f(width, height));
        shape->setPosition(x, y);
    }
    ~MockRectangle() {}
};

TEST(CollisionTest, NoCollision)
{
    MockRectangle rect1 = {0, 0, 10, 10};
    MockRectangle rect2 = {20, 20, 10, 10};
    EXPECT_FALSE(isIntersecting(rect1, rect2));
}

TEST(CollisionTest, PartialOverlap)
{
    MockRectangle rect1 = {0, 0, 10, 10};
    MockRectangle rect2 = {5, 5, 10, 10};
    EXPECT_TRUE(isIntersecting(rect1, rect2));
}

TEST(CollisionTest, FullOverlap)
{
    MockRectangle rect1 = {0, 0, 10, 10};
    MockRectangle rect2 = {0, 0, 10, 10};
    EXPECT_TRUE(isIntersecting(rect1, rect2));
}

TEST(CollisionTest, EdgeTouching)
{
    MockRectangle rect1 = {0, 0, 10, 10};
    MockRectangle rect2 = {10, 0, 10, 10};
    EXPECT_TRUE(isIntersecting(rect1, rect2));
}

TEST(CollisionTest, CornerTouching)
{
    MockRectangle rect1 = {0, 0, 10, 10};
    MockRectangle rect2 = {10, 10, 10, 10};
    EXPECT_TRUE(isIntersecting(rect1, rect2));
}

TEST(CollisionTest, InsideRectangle)
{
    MockRectangle rect1 = {0, 0, 20, 20};
    MockRectangle rect2 = {5, 5, 10, 10};
    EXPECT_TRUE(isIntersecting(rect1, rect2));
}
TEST(CollisionTest, InsideRectangle2)
{
    MockRectangle rect1 = {0, 0, 20, 20};
    MockRectangle rect2 = {5, 5, 10, 10};
    EXPECT_TRUE(isIntersecting(rect2, rect1));
}
TEST(CollisionTest, Intersection)
{
    Ball ball = {0, 0, 10};
    Block block1 = {0, 0, 10, 10};
    Block block2 = {60, 35, 100, 50};
    EXPECT_TRUE(isIntersecting(block1, ball));
    EXPECT_FALSE(isIntersecting(block2, ball));
}

TEST(CollisionTest, BallChangeSpeed)
{
    Ball ball = {0, 0};
    ball.velocity = {1, 1};
    Block block = {0, 0, 10, 10};
    testCollision(block, ball);
    EXPECT_EQ(ball.velocity.x, -1);
    EXPECT_EQ(ball.velocity.y, 1);
    EXPECT_TRUE(block.destroyed);
}
TEST(CollisionTest, BallNoChangeSpeed)
{
    Ball ball{0, 0, 10};
    ball.velocity = {1, 1};
    Block block = {60, 35, 100, 50};
    testCollision(block, ball);
    EXPECT_EQ(ball.velocity.x, 1);
    EXPECT_EQ(ball.velocity.y, 1);
    EXPECT_FALSE(block.destroyed);
}

TEST(CollisionTest, BallChangeSpeed2)
{
    Ball ball = {0, 0};
    ball.velocity = {1, 1};
    Block block = {0, 0, 10, 10};
    testCollision(block, ball);
    EXPECT_EQ(ball.velocity.x, -1);
    EXPECT_EQ(ball.velocity.y, 1);
    EXPECT_TRUE(block.destroyed);
}