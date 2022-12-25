#include "snakewidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SnakeWidget w;

    w.setWindowIcon(QIcon("../images/apple.png"));
    w.setWindowTitle("贪吃蛇");

    w.show();
    return a.exec();
}
