#ifndef CLOUDS_H
#define CLOUDS_H

#include <QObject>
#include <QGraphicsPixMapItem>

class clouds : public QObject, public QGraphicsPixmapItem
{
public:
    int x_ = 0;
    int y_ = 0;
    clouds(int x, int y);
};

#endif // CLOUDS_H
