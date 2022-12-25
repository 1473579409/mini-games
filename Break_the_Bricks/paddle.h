#ifndef PADDLE_H
#define PADDLE_H

#include "baseitem.h"

class Paddle: public BaseItem
{
public:
    Paddle(QObject *parent = nullptr);

    void resetState();
    void move();
    void setDx(int);

private:
    int dx; // 只有左右方向的移动
    static const int INITIAL_X = 200;
    static const int INITIAL_Y = 360;

};

#endif // PADDLE_H
