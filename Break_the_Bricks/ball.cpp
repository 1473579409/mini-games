#include "ball.h"

Ball::Ball(QObject *parent)
    : BaseItem{parent}
{
    image.load("../images/ball.png");
    rect = image.rect();
    resetState();
}

void Ball::resetState()
{
    ydir = -1;
    xdir = 1;
    rect.moveTo(INITIAL_X, INITIAL_Y);
}

// 球碰撞到上、左、右之后方向的变化
void Ball::autoMove()
{
    if (rect.left() == 0) { xdir = 1; }
    if (rect.right() == RIGHT_EDGE) { xdir = -1; }
    if (rect.top() == 0) { ydir = 1; }

    rect.translate(xdir, ydir);
}

void Ball::setXDir(int x)
{
    xdir = x;
}

void Ball::setYDir(int y)
{
    ydir = y;
}

int Ball::getXDir()
{
    return xdir;
}

int Ball::getYDir()
{
    return ydir;
}
