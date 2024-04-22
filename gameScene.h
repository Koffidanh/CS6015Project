#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "bucket.h"
#include "waterdrop.h"

#include "clouds.h"
#include <QMediaPlayer>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QUrl>
#include <QSoundEffect>
#include <QDialog>
#include <QMainWindow>
#include "scoredb.h"

class gameScene : public QGraphicsScene
{

public:
    const int dropletPoints = 5;
    const int maxMissedDroplets = 5;
    const int dropletsPerLevelIncrease = 5;
    const int maxSpeedLevel = 16;
    const int sceneWidth =908;
    const int sceneHeight = 510;
    int collectedDroplets = 0;
    int score = 0;
    int missedDroplets = 0;
    int dropletSpeedLevel = 1;
    int mode = 1;
    QSoundEffect *collectSound;
    QSoundEffect *missSound;
    QGraphicsTextItem *scoreText;
    QGraphicsTextItem *collectedDrops;
    QGraphicsTextItem *levelText;
    QPushButton *retryButton;
    QGraphicsView *view1;
    QString setUser;

    gameScene(QString user);
    void checkCollisions();
    void setupScoreDisplay();
    void adjustDropletSpeed();
    void showGameOverScreen();
    void clearScene();
    void setUpBucket();
    void setUpBackground();
    void loadClouds();
    void setDifficulty();
    void checkClose();
private slots:
    void openGameScene();
    void spawnWaterDrop();
    void updateScore();
    void gameOver();
    void retryGame();
    void setDifficultyEasy();
    void setDifficultyMedium();
    void setDifficultyHard();
};

#endif // GAMESCENE_H
