#include <QApplication>
#include <QGraphicsView>
#include "gameScene.h"


int main(int argc, char **argv) {
    QApplication app (argc, argv);
    gameScene *gamescene= new gameScene();
    QGraphicsView *mainView = new QGraphicsView();
    mainView->setFixedSize(910,512);
    mainView->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    mainView->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    mainView->setScene(gamescene);
    mainView->show();
    return app.exec();
}
