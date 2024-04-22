/** Class to handle cloud creation
 *
 *
 *
*/
#include "clouds.h"

clouds::clouds(int x, int y) {
    setPixmap(QPixmap("://images/cloud.png").scaled(150,150));
    setPos(x,y);
    x_ = x;
    y_ = y;
}
