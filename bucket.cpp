/** Class to handle bucket creation and  movement
 *
 *
 *
*/

#include "bucket.h"

bucket::bucket() {
    setPixmap(QPixmap("://images/bucket.png").scaled(150,150));
    setPos(x,y);
}

/**Method to handle character movement
 * @brief bucket::keyPressEvent
 * @param event
 */

void bucket::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Right and x < 800){
        x +=40;
        setPos(x,y);
    }

    if(event->key() == Qt::Key_Left and x > -10 ){
        x -=40;
        setPos(x,y);
    }

}
