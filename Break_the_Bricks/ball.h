#ifndef BALL_H
#define BALL_H

#include "baseitem.h"

class Ball : public BaseItem
{
    Q_OBJECT
public:
    explicit Ball(QObject *parent = nullptr);
public:
    void resetState();
    void autoMove();
    void setXDir(int);
    void setYDir(int);
    int getXDir();
    int getYDir();
private:
    int xdir;
    int ydir;
    static const int INITIAL_X = 230;
    static const int INITIAL_Y = 355;
};

#endif // BALL_H
