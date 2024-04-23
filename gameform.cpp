/** Class to handle the game selection screen with user data, picture, and games available, plus scores.
 *
 *
 *
 */

#include "gameform.h"
#include "ui_gameform.h"

GameForm::GameForm(MainWindow::User *userInfo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameForm)
{
    ui->setupUi(this);
    addUserInfo(userInfo);
    playerName = userInfo->userName;

    //check for user birthday to popup message.
    if(isBirthday(userInfo->birthdate)){
        QDialog *confirmation = new QDialog();
        QGridLayout *gridConfirm = new QGridLayout(confirmation);
        QTextEdit *success = new QTextEdit("Happy Birthday " + userInfo->firstName + " " + userInfo->lastName + " !!!!");
        QPushButton *confirmButton = new QPushButton("OK");
        gridConfirm->addWidget(success,0,10);
        gridConfirm->addWidget(confirmButton,0,30);
        connect(confirmButton, &QPushButton::clicked, confirmation, &QDialog::accept);
        confirmation->exec();
    }


}

GameForm::~GameForm()
{
    delete ui;
}

/**Method to add user info to the screen
 *
 * @param userData - user data to add to screen
 */
void GameForm::addUserInfo(MainWindow::User *userData){
    QString createString;
    QDate currentDate = QDate::currentDate();
    createString = "Welcome " + userData->firstName + " " + userData->lastName + "! \n" +"Todays date is: " + currentDate.toString();
    ui->SuccessPage->setText(createString);
    //check to make sure image was uploaded.
    if(!userData->profileImage.isEmpty()){
    // QString getStartPath = "://images/";
    QPixmap *getImage = new QPixmap(QCoreApplication::applicationDirPath() + "/" + userData->profileImage);
    QSize imageSize = ui->profilePic->size();

    QPixmap scaledImage = getImage->scaled(imageSize, Qt::KeepAspectRatio);
    ui->profilePic->setPixmap(scaledImage);


    }
}


/**Button to start game.
 * @brief
 */
void GameForm::on_playBtn_clicked()
{
     gameScene *startGame = new gameScene(playerName);


}

/** Method to check for user birthday.
 *
 * @param birthdate - user birthdate to check
 * @return if user birthday
 */
bool GameForm::isBirthday(QString birthdate) {
    // Assuming the birthdate format is "YYYY-MM-DD"
    QDate currentDate = QDate::currentDate();
    QDate birthDate = QDate::fromString(birthdate, "yyyy-MM-dd");

    return currentDate.month() == birthDate.month() && currentDate.day() == birthDate.day();
}

/**
 * @brief Button to get users scores and top score.
 */
void GameForm::on_pushButton_clicked()
{
    ScoreDB *getScores = new ScoreDB();
    QString allScores;
    int maxScore=0;
    //loop through and get only users score, and top score.
    foreach(ScoreDB::scoreData *oneScore, getScores->existingScores){
        if(oneScore->score > maxScore){
            maxScore=oneScore->score;
        }
        if(playerName == oneScore->user){
            QString scoreString = QString::number(oneScore->score);
            allScores += oneScore->user + " " + scoreString + "<br>";
        }
    }

    QString scoreToInt = "Global High Score: " + QString::number(maxScore) + "<br>";
    QString combinedValues = scoreToInt + allScores;
    QDialog *scores = new QDialog();
    QGridLayout *gridConfirm = new QGridLayout(scores);
    QTextEdit *success = new QTextEdit(combinedValues);
    QPushButton *confirmButton = new QPushButton("OK");
    gridConfirm->addWidget(success,0,10);
    gridConfirm->addWidget(confirmButton,0,30);
    connect(confirmButton, &QPushButton::clicked, scores, &QDialog::accept);
    scores->exec();
}

