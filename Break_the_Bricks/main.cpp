#include "breakoutwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BreakoutWidget w;
    w.setWindowIcon(QIcon("../images/ball.png"));
    w.setWindowTitle("打砖块");
    w.show();
    return a.exec();
}
