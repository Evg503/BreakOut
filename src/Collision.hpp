#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "config.hpp"
#include <algorithm>

template <class T1, class T2>
bool isIntersecting(T1 &mA, T2 &mB)
{
    return mA.right() >= mB.left() && mA.left() <= mB.right() &&
           mA.bottom() >= mB.top() && mA.top() <= mB.bottom();
}

inline void testCollision(Paddle &mPaddle, Ball &mBall)
{
    if (!isIntersecting(mPaddle, mBall))
        return;

    float velocity = sqrt(mBall.velocity.x * mBall.velocity.x + mBall.velocity.y * mBall.velocity.y);
    velocity = std::clamp(velocity, minballVelocity, maxballVelocity);
    auto angle = 2 * (mPaddle.x() - mBall.x()) / (mPaddle.left() - mPaddle.right()); // ~[-2..2]
    mBall.velocity.x = velocity * sin(angle);
    mBall.velocity.y = -velocity * cos(angle);
}

inline bool testCollision(Block &mBlock, Ball &mBall)
{
    if (mBlock.destroyed || !isIntersecting(mBlock, mBall))
        return false;

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
    {
        mBall.velocity.x = -mBall.velocity.x;
        mBall.move(minOverlapX * (ballFromLeft ? 1 : -1), 0);
    }
    else
    {
        mBall.velocity.y = -mBall.velocity.y;
        mBall.move(0, minOverlapY * (ballFromTop ? 1 : -1));
    }
    return true;
}
