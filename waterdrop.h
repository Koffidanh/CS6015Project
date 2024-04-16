#ifndef WATERDROP_H
#define WATERDROP_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bucket.h"
#include <QGraphicsScene>
#include <QtMultimedia>


class waterDrop : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    int x;
    int y = 100;
    int waterDropCollects = 0;
    int speedMultiplier = 1;
    explicit waterDrop(int initialSpeed, QObject *parent = nullptr);
    void move_droplet();

public slots:
  void timeDropMove(int speedMult);
signals:
    void collected();
    void missed();

};

#endif // WATERDROP_H
