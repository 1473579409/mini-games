#ifndef BREAKOUTWIDGET_H
#define BREAKOUTWIDGET_H

#include <QWidget>
#include "brick.h"
#include "ball.h"
#include "paddle.h"

class BreakoutWidget : public QWidget
{
    Q_OBJECT

public:
    BreakoutWidget(QWidget *parent = nullptr);
    ~BreakoutWidget();
    void finishGame(QPainter *, QString);
    void startGame();
    void pauseGame();
    void stopGame();
    void victory();
    void checkCollision();
private:
    void checkPaddleCollision();
    void checkBricksCollision();
protected:
    void timerEvent(QTimerEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
private:
    int timerId;
    static const int N_OF_BRICKS = 30;
    static const int DELAY = 10;
    static const int BOTTOM_EDGE = 400;

    Ball * ball;
    Paddle * paddle;
    Brick * bricks[N_OF_BRICKS];

    bool gameOver;
    bool gameWon;
    bool gameStarted;
    bool paused;
    unsigned brokenBricks;



};
#endif // BREAKOUTWIDGET_H
