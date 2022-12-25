#include "brick.h"

Brick::Brick(int x, int y, QObject *parent)
{
    destroyed = false;
    image.load("../images/brick.png");
    rect=image.rect();
    rect.translate(x,y);
    //static int i=0;
    //this->setObjectName("Brick"+QString::number(++i));
}

bool Brick::isDestroyed()
{
    return destroyed;
}

void Brick::setDestroyed(bool b)
{
    destroyed = b;
}
