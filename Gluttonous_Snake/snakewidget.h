#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QWidget>

class SnakeWidget : public QWidget
{
    Q_OBJECT

public:
    SnakeWidget(QWidget *parent = nullptr);
    ~SnakeWidget();
    enum moveDirection {
        left,
        right,
        up,
        down
    };

protected:
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QImage dot; //身体的一节
    QImage head;
    QImage apple;
    moveDirection heading;
    static const int B_WIDTH = 300;
    static const int B_HEIGHT = 300;
    static const int DOT_SIZE = 10;                                         //身体一节的大小，10*10
    static const int ALL_DOTS = B_WIDTH * B_HEIGHT / (DOT_SIZE *DOT_SIZE);  // 900 最大布局 最大蛇的身体节数

    int timerId;
    int length_snake; // 蛇当前的长度
    int apple_x;
    int apple_y;
    bool game_playing;
    int x[ALL_DOTS]; // 蛇每一节身体的位置
    int y[ALL_DOTS];
    void initGame();
    void locateApple(); // 初始化苹果的位置

    void move();
    void checkApple();
    void checkCollision();
    void gameOver(QPainter &);
};
#endif // SNAKEWIDGET_H
