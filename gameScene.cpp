/** Class to handle the main game scene, water drop creation, and movement.
 *
 *
 *
*/

#include "gameScene.h"


gameScene::gameScene() {
    setUpBackground();
    //
    // easyButton = new QPushButton("Easy");
    // mediumButton = new QPushButton("Medium");
    // hardButton = new QPushButton("Hard");

    // QObject::connect(easyButton, &QPushButton::clicked, this, &gameScene::setDifficultyEasy);
    // QObject::connect(mediumButton, &QPushButton::clicked, this, &gameScene::setDifficultyMedium);
    // QObject::connect(hardButton, &QPushButton::clicked, this, &gameScene::setDifficultyHard);

    // this->addWidget(easyButton);
    // this->addWidget(easyButton);
    // this->addWidget(easyButton);



    //
    setUpBucket();
    loadClouds();
    //load timer for drops
    QTimer *timer_drop = new QTimer(this);
    connect(timer_drop, &QTimer::timeout, this, &gameScene::spawnWaterDrop);
    timer_drop->start(3000);


    setupScoreDisplay();

}

void gameScene::setUpBackground(){
    setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512) .scaledToWidth(910)));
    setSceneRect(0,0,908,510);
}

void gameScene::setUpBucket(){
    bucket *bucketItem = new bucket();
    bucketItem->setFlag(QGraphicsItem::ItemIsFocusable);
    bucketItem->setFocus();
    addItem(bucketItem);
}

void gameScene::loadClouds(){
    //array to load clouds
    int cloudY = 0;
    int cloudX = 0;
    for(int i=0;i<6; i++){
        clouds *genCloud = new clouds(cloudX, cloudY);
        cloudX+=150;
        addItem(genCloud);
    }

}
/** Method for spawning drops
 * @brief gameScene::spawnWaterDrop
 */

void gameScene::spawnWaterDrop() {
    waterDrop *droplet = new waterDrop(dropletSpeedLevel);
    connect(droplet, &waterDrop::collected, this, &gameScene::updateScore);
    connect(droplet, &waterDrop::missed, this, &gameScene::gameOver);
    this->addItem(droplet);
}

void gameScene::setupScoreDisplay() {
    scoreText = new QGraphicsTextItem();
    scoreText->setPlainText("Score: " + QString::number(score));
    scoreText->setPos(30, 50);
    QFont f;
    f.setPointSize(15);
    scoreText->setFont(f);
    scoreText->setDefaultTextColor(Qt::black);
    addItem(scoreText);

    collectedDrops = new QGraphicsTextItem();
    collectedDrops->setPlainText("Drops: " + QString::number(collectedDroplets));
    collectedDrops->setPos(30, 80);
    collectedDrops->setFont(f);
    collectedDrops->setDefaultTextColor(Qt::black);
    addItem(collectedDrops);

}

void gameScene::updateScore() {
    score += dropletPoints;
    collectedDroplets++;

    if(collectedDroplets % 5 == 0){
        if(dropletSpeedLevel <=16)
        dropletSpeedLevel*=2;
        else{
            dropletSpeedLevel = 16;
        }
    }

    scoreText->setPlainText("Score: " + QString::number(score));

    collectedDrops->setPlainText("Drops: " + QString::number(collectedDroplets));
    // adjustDropletSpeed();

    // collectSound->play();
}

void gameScene::gameOver() {

    missedDroplets++;

    // missedText->setPlainText("Missed: " + QString::number(missedDroplets));
    // missSound->play();

    if (missedDroplets > 5 || score >= 150) {
        showGameOverScreen();
    }

}

void gameScene::showGameOverScreen() {
    if(missedDroplets > 5){
    QGraphicsTextItem *gameOverText = new QGraphicsTextItem();
    gameOverText->setPlainText("Game Over!");
    gameOverText->setPos(sceneWidth / 2-100, sceneHeight / 2-50);
    gameOverText->setDefaultTextColor(Qt::red);
    QFont f;
    f.setPointSize(50);
    gameOverText->setFont(f);
    addItem(gameOverText);
    }
    if(score >= 150){
        QGraphicsTextItem *gameWinText = new QGraphicsTextItem();
        gameWinText->setPlainText("You Win!");
        gameWinText->setPos(sceneWidth / 2-100, sceneHeight / 2-50);
        gameWinText->setDefaultTextColor(Qt::green);
        QFont f;
        f.setPointSize(50);
        gameWinText->setFont(f);
        addItem(gameWinText);

    }

    retryButton = new QPushButton("Retry");
    retryButton->setGeometry(sceneWidth / 2 - 25, sceneHeight / 2 + 20, 50, 25);
    connect(retryButton, &QPushButton::clicked, this, &gameScene::retryGame,Qt::QueuedConnection);
    // QObject::connect(retryButton, SIGNAL(&QPushButton::clicked), this, SLOT(&gameScene::retryGame()), Qt::QueuedConnection);


    addWidget(retryButton);
}

void gameScene::retryGame() {
    disconnect();

    QList<QGraphicsItem*> allItems = items();
    for (QGraphicsItem* item : allItems) {
        removeItem(item);
        delete item; // If the item was dynamically allocated
    }

    collectedDroplets = 0;
    score = 0;
    missedDroplets = 0;
    dropletSpeedLevel = 1*mode;

    setUpBackground();
    setUpBucket();
    loadClouds();
    setupScoreDisplay();

    QTimer *timerDrop = new QTimer(this);
    connect(timerDrop, &QTimer::timeout, this, &gameScene::spawnWaterDrop);
    timerDrop->start(3000/dropletSpeedLevel);
}

void gameScene::setDifficultyEasy(){
    dropletSpeedLevel*=1;
    mode = 1;
}
void  gameScene::setDifficultyMedium(){
    dropletSpeedLevel*=2;
    mode=2;
}
void  gameScene::setDifficultyHard(){
    dropletSpeedLevel*=3;
    mode=3;
}
