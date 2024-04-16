/** Class to handle water drop creation and movement
 *
 *
 *
*/
#include "waterdrop.h"

waterDrop::waterDrop(int initialSpeed, QObject *parent)
    : QObject{parent}
{
    setPixmap((QPixmap(":/images/water.gif")).scaled(30,30));
    //pick a random x to start
    this->x = arc4random() % 800;
    setPos(x,100);
    timeDropMove(initialSpeed);
}

/** Method to handle movement of water drops
 * @brief waterDrop::move_droplet
 */

void waterDrop::move_droplet(){

    //check for collisions
    QList<QGraphicsItem*> collidingItems = this->collidingItems();
    foreach(QGraphicsItem *item, collidingItems) {
        if (dynamic_cast<bucket*>(item)) {
            emit collected();
            scene()->removeItem(this);
            delete this;

            return;
        }
    }

    //move down 50
    y +=50;

    //check if off screen
    if(y > 510){
        emit missed();
        scene()->removeItem(this);
        delete this;

    }
    else{
    setPos(x,y);
    }



}

/** Method for handling time water movement.
 * @brief waterDrop::timeDropMove
 */
void waterDrop::timeDropMove(int speedMult){
    QTimer *timer_drop = new QTimer(this);
    connect(timer_drop, &QTimer::timeout, this, &waterDrop::move_droplet);
    timer_drop->start(2000/speedMult);
}


