#include "snakewidget.h"
#include <QTime>
#include <QRandomGenerator>
#include <QPainter>
SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent)
{
    grabKeyboard(); // 避免非顶层组件拿不到键盘按下事件信号
    dot.load("../images/dot.png"); //身体的一节
    head.load("../images/head.png");
    apple.load("../images/apple.png");

    setFixedSize(B_WIDTH, B_HEIGHT);

    initGame();
}

SnakeWidget::~SnakeWidget()
{
}

void SnakeWidget::timerEvent(QTimerEvent *event)
{
    if (game_playing) {
        checkApple();
        move();
        checkCollision();
    }
    repaint();
}
#include <QKeyEvent>
void SnakeWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();

    // 不与逻辑冲突，改变方向
    switch (key) {
        case Qt::Key_Left:
            if (heading != right) {
                heading = left;
            }
            break;
        case Qt::Key_Right:
            if (heading != left) {
                heading = right;
            }
            break;
        case Qt::Key_Up:
            if (heading != down) {
                heading = up;
            }
            break;
        case Qt::Key_Down:
            if (heading != up) {
                heading = down;
            }
            break;
        default:
            break;
    }

    //若 GameOver 按下空格重新启动
    if (key == Qt::Key_Space && game_playing == false) {
        initGame();
    }

    QWidget::keyPressEvent(event);
}

void SnakeWidget::paintEvent(QPaintEvent *event)
{
    QPainter qp(this);

    // 蛇头如果超过了边界或者对自身碰撞，结束绘制
    if (game_playing) {
        qp.drawImage(apple_x, apple_y, apple);

        for (int i = 0; i < length_snake; i++) {
            if (i == 0) {
                qp.drawImage(x[i], y[i], head);
            } else {
                qp.drawImage(x[i], y[i], dot);
            }
        }
    } else {
        gameOver(qp);
    }
}

void SnakeWidget::initGame()
{
    setStyleSheet("background-color:black;");
    heading = right;
    length_snake = 3;
    game_playing = true; // 游戏结束时为false,重启时为true

    for (int i = 0; i < length_snake; i++) {
        x[i] = 50 - i * DOT_SIZE; // 显示蛇的初始长度，并将蛇头设置在第五行第五列
        y[i] = 50;
    }

    locateApple();

    timerId = startTimer(100);
}

// 随机位置生成苹果
void SnakeWidget::locateApple()
{
    //    QTime time=QTime::currentTime();
    //    std::srand((unsigned int)time.second());

    //    int r=rand()%(B_WIDTH/DOT_SIZE); // 0-29
    int r = QRandomGenerator::global()->bounded(B_WIDTH / DOT_SIZE);
    apple_x = r * DOT_SIZE;
    //    r=rand()%(B_HEIGHT/DOT_SIZE);
    r = QRandomGenerator::global()->bounded(B_HEIGHT / DOT_SIZE);
    apple_y = r * DOT_SIZE;
}

void SnakeWidget::move()
{
    // 蛇在转动时的算法
    for (int i = length_snake - 1; i > 0; --i) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    // 更新新的蛇头位置
    switch (heading) {
        case left:
            x[0] -= DOT_SIZE;
            break;
        case right:
            x[0] += DOT_SIZE;
            break;
        case up:
            y[0] -= DOT_SIZE;
            break;
        case down:
            y[0] += DOT_SIZE;
            break;
    }
}

// 蛇头与苹果碰撞的情况
void SnakeWidget::checkApple()
{
    if ((x[0] == apple_x) && (y[0] == apple_y)) {
        ++length_snake;
        locateApple();
    }
}

// 蛇对自身或边框碰撞的情况
void SnakeWidget::checkCollision()
{
    if (length_snake > 4) // 优化剪枝，不可能发生碰撞的情况
        for (int i = length_snake - 1; i > 0; i--) {
            if ((x[0] == x[i]) && (y[0] == y[i])) {
                game_playing = false;
            }
        }

    // 边框碰撞
    if (x[0] >= B_WIDTH || x[0] < 0 || y[0] >= B_HEIGHT || y[0] < 0) {
        game_playing = false;
    }

    if (game_playing == false) {
        killTimer(timerId);
    }
}

// 游戏结束，绘制结束界面显示
void SnakeWidget::gameOver(QPainter &qp)
{
    setStyleSheet("background-color:white;");
    QString message = "Game Over!!!";
    QFont font("Courier", 15);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);
    int textHeight = fm.height();
    qp.setFont(font);
    int h = height();
    int w = width();

    // 移动到屏幕中间，通过scene坐标，将画笔移动到左上角
    qp.translate(w / 2, h / 2);
    qp.drawText(-textWidth / 2, -textHeight / 2, message);
    // qp.drawText(-textWidth/2,+textHeight/2, "按空格重新开始");
}
