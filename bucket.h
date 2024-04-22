#ifndef BUCKET_H
#define BUCKET_H

#include <QGraphicsPixMapItem>
#include <QKeyEvent>
#include <QObject>

class bucket : public QObject, public QGraphicsPixmapItem
{
public:
    int x = 400;
    int y=365;
    bucket();
    void keyPressEvent(QKeyEvent *event);
};

#endif // BUCKET_H
