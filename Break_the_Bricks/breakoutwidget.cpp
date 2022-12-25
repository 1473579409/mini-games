#include "breakoutwidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <QApplication>

BreakoutWidget::BreakoutWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color:gray");
    setFixedSize(300, 400);

    ball = new Ball(this);
    paddle = new Paddle(this);

    //Brick * bricks[N_OF_BRICKS];
    const int paddle_w = paddle->getRect().width();
    const int paddle_h = paddle->getRect().height();
    for (int i = 0, k = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            // 将点[30,50]作为起始点，并开始绘制一组5行6列的砖块
            bricks[k++] = new Brick(30 + j * paddle_w, 50 + i * paddle_h, this);
        }
    }

    gameOver = false;
    gameWon = false;
    gameStarted = false;
    paused = false;

}

void BreakoutWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (gameOver) {
        finishGame(&painter, "Game Over");
    } else if (gameWon) {
        finishGame(&painter, "Victory");
    } else {
        painter.drawImage(ball->getRect(), ball->getImage());
        painter.drawImage(paddle->getRect(), paddle->getImage());

        for (int i = 0; i < N_OF_BRICKS; ++i) {
            if (!bricks[i]->isDestroyed()) {
                painter.drawImage(bricks[i]->getRect(), bricks[i]->getImage());
            }
        }
    }
}

void BreakoutWidget::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Left: paddle->setDx(-1); break;
        case Qt::Key_Right: paddle->setDx(1); break;
        case Qt::Key_P: pauseGame(); break;
        case Qt::Key_Space: startGame(); break;
        case Qt::Key_Escape: qApp->exit(); break;
        default: QWidget::keyPressEvent(e); // 交给父类处理
    }
}

void BreakoutWidget::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key()) {
        case Qt::Key_Left:; // 键位释放时，停止弹板移动
        case Qt::Key_Right: paddle->setDx(0); break;
        default: QWidget::keyReleaseEvent(e);
    }
}


BreakoutWidget::~BreakoutWidget()
{
}

void BreakoutWidget::finishGame(QPainter *painter, QString message)
{
    setStyleSheet("background-color:white;");
    QFont font("Courier", 15);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);

    painter->setFont(font);
    int h = height();
    int w = width();

    painter->translate(QPoint(w / 2, h / 2));
    painter->drawText(-textWidth / 2, 0, message);
}

void BreakoutWidget::startGame()
{
    if (!gameStarted) {
        setStyleSheet("background-color:gray;");
        ball->resetState();
        paddle->resetState();

        for (int i = 0; i < N_OF_BRICKS; ++i) {
            bricks[i]->setDestroyed(false); // 重新设置所有砖块状态
        }

        gameOver = false;
        gameWon = false;
        gameStarted = true;
        timerId = startTimer(DELAY);
        brokenBricks = 0;
    }
}

void BreakoutWidget::pauseGame()
{
    if (paused) {
        paused = false;
        killTimer(timerId);
    } else {
        paused = true;
        timerId = startTimer(DELAY);
    }
}

void BreakoutWidget::stopGame()
{
    gameOver = true;
    gameStarted = false;
    killTimer(timerId);
}

void BreakoutWidget::victory()
{
    gameWon = true;
    gameStarted = false;
    killTimer(timerId);
}

void BreakoutWidget::checkCollision()
{
    // 判断球的底部坐标 y 是否超过了底部边框的大小
    if (ball->getRect().bottom() > BOTTOM_EDGE) {
        stopGame();
        return;
    }
    checkPaddleCollision();
    checkBricksCollision();
    if (brokenBricks >= N_OF_BRICKS) { victory(); }

}

void BreakoutWidget::checkPaddleCollision()
{
    if (ball->getRect().intersects(paddle->getRect())) {
        int paddleLPos = paddle->getRect().left();
        int ballLPos = ball->getRect().left();
        int oneFifthPaddle = paddle->getRect().width() / 5;
        int twoFifthPaddlePos = paddleLPos + 2 * oneFifthPaddle;
        int threeFifthPaddlePos = paddleLPos + 3 * oneFifthPaddle;
        if (ballLPos < twoFifthPaddlePos) { ball->setXDir(-1); } // 球碰撞到弹板的左边(2/5处)
        if (ballLPos >= twoFifthPaddlePos && ballLPos < threeFifthPaddlePos) { ball->setXDir(0); }
        if (ballLPos >= threeFifthPaddlePos) { ball->setXDir(1); } // 球碰撞到弹板的右边(大于3/5处)

        ball->setYDir(-1);
    }
}

void BreakoutWidget::checkBricksCollision()
{
    for (int i = 0; i < N_OF_BRICKS; i++) {
        if (bricks[i]->isDestroyed()) { continue; }
        if (ball->getRect().intersects(bricks[i]->getRect())) {
            int ballLeft = ball->getRect().left();
            int ballHeight = ball->getRect().height();
            int ballWidth = ball->getRect().width();
            int ballTop = ball->getRect().top();
            // 使用球相对矩形对角的四个点作碰撞检测的基准
            QPoint pointRight(ballLeft + ballWidth, ballTop/*+ballHeight/2*/); // 也可以选用球的上下左右
            QPoint pointLeft(ballLeft, ballTop);
            QPoint pointTop(ballLeft, ballTop);
            QPoint pointBottom(ballLeft, ballTop + ballHeight);

            // 小球是否碰到砖块
            if (bricks[i]->getRect().contains(pointRight)) { ball->setXDir(-1); } // 球弹向左
            if (bricks[i]->getRect().contains(pointLeft)) { ball->setXDir(1); } // 右
            if (bricks[i]->getRect().contains(pointTop)) { ball->setYDir(1); } // 下
            if (bricks[i]->getRect().contains(pointBottom)) { ball->setYDir(-1); } // 上

            bricks[i]->setDestroyed(true);
            ++brokenBricks;
            break;
        }
    }
}

void BreakoutWidget::timerEvent(QTimerEvent *event)
{
    ball->autoMove();
    paddle->move();

    checkCollision();
    repaint();
}

