#ifndef BASEITEM_H
#define BASEITEM_H

#include <QObject>
#include <QImage>
#include <QRect>

// 抽象出个各类中的共有属性
class BaseItem : public QObject
{
    Q_OBJECT
public:
    QRect getRect();
    QImage &getImage();
protected:
    QImage image;
    QRect rect;
    explicit BaseItem(QObject *parent = nullptr);
    virtual ~BaseItem();

    static const int RIGHT_EDGE = 300;
};

#endif // BASEITEM_H
