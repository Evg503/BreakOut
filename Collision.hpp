#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Paddle.hpp"
#include "Ball.hpp"
#include "Block.hpp"
#include "config.hpp"


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
