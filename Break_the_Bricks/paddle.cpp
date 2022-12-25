#include "paddle.h"

Paddle::Paddle(QObject *parent)
    : BaseItem{parent}
{
    image.load("../images/paddle.png");

    rect = image.rect();
    resetState();
    //this->setObjectName("Paddle");
}

void Paddle::resetState()
{
    setDx(0);
    rect.moveTo(INITIAL_X, INITIAL_Y);
}

void Paddle::move()
{

    int x = rect.x() + dx;
    int y = rect.y();

    // 通过判断左边空间是否小于右边框减去弹板的宽度，决定能否移动弹板
    if ((x > 0) && (x < RIGHT_EDGE - rect.width())) {
        rect.moveTo(x, y);
    }
}

void Paddle::setDx(int x)
{
    dx = x;
}
