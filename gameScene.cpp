/** Class to handle the main game scene, water drop creation, and movement.
 *
 *
 *
*/

#include "gameScene.h"
#include "QtWidgets/qgraphicsview.h"


gameScene::gameScene(QString user) {

    setDifficulty();
    //load sounds.
    collectSound = new QSoundEffect();
    collectSound->setSource(QUrl::fromLocalFile("://water-droplet-1.wav"));
    collectSound->setLoopCount(1);
    collectSound->setVolume(100);
    collectSound->setMuted(false);
    missSound = new QSoundEffect();
    missSound->setSource(QUrl::fromLocalFile("://fail-trombone-01.wav"));
    missSound->setLoopCount(1);
    missSound->setVolume(100);

    //set up objects
     setUpBackground();
    setUpBucket();
    loadClouds();
    //load timer for drops
    QTimer *timer_drop = new QTimer(this);
    connect(timer_drop, &QTimer::timeout, this, &gameScene::spawnWaterDrop);
    timer_drop->start(3000);

    //create timer to check close events for deletion.
    QTimer *closeChecker = new QTimer(this);
    connect(closeChecker, &QTimer::timeout, this, &gameScene::checkClose);
    closeChecker->start(500);

    setUser = user;

    setupScoreDisplay();


    view1 = new QGraphicsView();
    view1->setScene(this);


    view1->show();
    view1->setFocus();

}

/**
 * @brief Method to check if game is close to delete objects.
 */
void gameScene::checkClose(){
    if(!view1->isVisible()){

        disconnect();

        QList<QGraphicsItem*> allItems = items();
        for (QGraphicsItem* item : allItems) {
            removeItem(item);
            delete item;
        }
        view1->close();
    }
}

/**
 * @brief Method to set the difficulty depending on the button clicked.
 */

void gameScene::setDifficulty(){
    QDialog *difficultyDialog = new QDialog();
    QGridLayout *gridLayout = new QGridLayout(difficultyDialog);
    // Add buttons for easy, medium, and hard difficulty to the grid layout
    QPushButton *easyButton = new QPushButton("Easy");
    QPushButton *mediumButton = new QPushButton("Medium");
    QPushButton *hardButton = new QPushButton("Hard");
    QPushButton *startButton = new QPushButton("Start");

    hardButton->setCheckable(true);
    hardButton->setStyleSheet(QString("QPushButton {background-color: red;}"));
    mediumButton->setCheckable(true);
    mediumButton->setStyleSheet(QString("QPushButton {background-color: blue;}"));
    easyButton->setCheckable(true);
    easyButton->setStyleSheet(QString("QPushButton {background-color: green;}"));
    gridLayout->addWidget(easyButton, 0, 0);
    gridLayout->addWidget(mediumButton, 0, 1);
    gridLayout->addWidget(hardButton, 0, 2);
    gridLayout->addWidget(startButton, 1, 0, 1, 3);

    connect(easyButton, &QPushButton::clicked, this, &gameScene::setDifficultyEasy);
    connect(mediumButton, &QPushButton::clicked, this, &gameScene::setDifficultyMedium);
    connect(hardButton, &QPushButton::clicked, this, &gameScene::setDifficultyHard);
    connect(startButton, &QPushButton::clicked, difficultyDialog, &QDialog::accept);

    difficultyDialog->exec();



}

/**
 * @brief Method to open game.
 */
void gameScene::openGameScene(){
    QGraphicsView *view1 = new QGraphicsView();
    view1->setScene(this);
    view1->show();
}

/**
 * @brief Method to set up game background.
 */
void gameScene::setUpBackground(){
    setBackgroundBrush(QBrush(QImage(":/images/background.jpg").scaledToHeight(512) .scaledToWidth(910)));
    setSceneRect(0,0,908,510);
}

/**Method to set up bucket
 *
 */
void gameScene::setUpBucket(){
    bucket *bucketItem = new bucket();
    bucketItem->setFlag(QGraphicsItem::ItemIsFocusable);
    bucketItem->setFocus();
    addItem(bucketItem);
}

/**Method to load clouds.
 *
 */
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

/**Method to set up score display on screen
 *
 */
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

/**
 * @brief Method to update score.
 */
void gameScene::updateScore() {
    score += dropletPoints;
    collectedDroplets++;

    if(collectedDroplets % 5 == 0){
        //max allowed speed.
        if(dropletSpeedLevel <=16)
        dropletSpeedLevel*=2;
        else{
            dropletSpeedLevel = 16;
        }
    }

    scoreText->setPlainText("Score: " + QString::number(score));

    collectedDrops->setPlainText("Drops: " + QString::number(collectedDroplets));

    collectSound->play();
}

/**
 * @brief method to handle game over.
 */
void gameScene::gameOver() {

    missedDroplets++;

    missSound->play();

    //check both win and lose conditions.
    if (missedDroplets > 5 || score >= 150) {
        showGameOverScreen();
    }

}

/**
 * @brief Method to create game over screen and add score to file.
 */
void gameScene::showGameOverScreen() {
    //add users score to file.
     ScoreDB::updateFile(setUser, score);
    //loss condition
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
    //win condition.
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
    addWidget(retryButton);
}
/**
 * @brief Method to handle retry button if user wants to play again.
 */
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

/**Methods below are all for setting difficulty.
 *
 */
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
