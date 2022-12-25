#ifndef BRICK_H
#define BRICK_H

#include "baseitem.h"

class Brick : public BaseItem
{
    Q_OBJECT
public:
    Brick(int, int, QObject *parent = nullptr);
    bool isDestroyed();
    void setDestroyed(bool);
private:
    bool destroyed;

};

#endif // BRICK_H
