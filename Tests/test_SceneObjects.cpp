#include <gtest/gtest.h>

#include "Paddle.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "Collision.hpp"

// Example test case for SceneObject class
TEST(SceneObjectTest, PaddleConstructor)
{
    Paddle obj(100, 200);
    EXPECT_FLOAT_EQ(obj.x(), 100);
    EXPECT_FLOAT_EQ(obj.y(), 200);
    EXPECT_FLOAT_EQ(obj.left(), 100 - 30);
    EXPECT_FLOAT_EQ(obj.right(), 130);
    EXPECT_FLOAT_EQ(obj.top(), 200 - 10);
    EXPECT_FLOAT_EQ(obj.bottom(), 210);
}

TEST(SceneObjectTest, BallConstructor)
{
    Ball obj(100, 200, 15);
    EXPECT_FLOAT_EQ(obj.x(), 100);
    EXPECT_FLOAT_EQ(obj.y(), 200);
    EXPECT_NEAR(obj.left(), 100 - 15, 1);
    EXPECT_NEAR(obj.right(), 115, 1);
    EXPECT_FLOAT_EQ(obj.top(), 200 - 15);
    EXPECT_FLOAT_EQ(obj.bottom(), 215);
}

TEST(SceneObjectTest, BlockConstructor)
{
    Block obj(300, 400, 100, 40);
    EXPECT_FLOAT_EQ(obj.x(), 300);
    EXPECT_FLOAT_EQ(obj.y(), 400);
    EXPECT_FLOAT_EQ(obj.left(), 250);
    EXPECT_FLOAT_EQ(obj.right(), 350);
    EXPECT_FLOAT_EQ(obj.top(), 380);
    EXPECT_FLOAT_EQ(obj.bottom(), 420);
}

TEST(SceneObjectTest, PaddleMove)
{
    Paddle obj(100, 200);
    obj.move(10, 20);
    EXPECT_FLOAT_EQ(obj.x(), 110);
    EXPECT_FLOAT_EQ(obj.y(), 220);
    EXPECT_FLOAT_EQ(obj.left(), 110 - 30);
    EXPECT_FLOAT_EQ(obj.right(), 140);
    EXPECT_FLOAT_EQ(obj.top(), 210);
    EXPECT_FLOAT_EQ(obj.bottom(), 230);
}
TEST(SceneObjectTest, BallMove)
{
    Ball obj(100, 200, 50);
    obj.move(1, 2);
    EXPECT_FLOAT_EQ(obj.x(), 101);
    EXPECT_FLOAT_EQ(obj.y(), 202);
    EXPECT_NEAR(obj.left(), 51, 1);
    EXPECT_NEAR(obj.right(), 151, 1);
    EXPECT_FLOAT_EQ(obj.top(), 152);
    EXPECT_FLOAT_EQ(obj.bottom(), 252);
}

TEST(SceneObjectTest, BlockMove)
{
    Block obj(300, 400, 100, 40);
    obj.move(10, 20);
    EXPECT_FLOAT_EQ(obj.x(), 310);
    EXPECT_FLOAT_EQ(obj.y(), 420);
    EXPECT_FLOAT_EQ(obj.left(), 260);
    EXPECT_FLOAT_EQ(obj.right(), 360);
    EXPECT_FLOAT_EQ(obj.top(), 400);
    EXPECT_FLOAT_EQ(obj.bottom(), 440);
}
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}