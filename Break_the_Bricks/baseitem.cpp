#include "baseitem.h"

QRect BaseItem::getRect()
{
    return rect;
}

QImage &BaseItem::getImage()
{
    return image;
}

BaseItem::BaseItem(QObject *parent)
    : QObject{parent}
{
    //this->setObjectName("BaseItem");//如果派生类有自己的版本，会被覆盖
}

BaseItem::~BaseItem()
{
    //qInfo()<<this->objectName()<<"destroyed"<<Qt::endl;
}
