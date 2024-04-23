#ifndef GAMEFORM_H
#define GAMEFORM_H

#include <QWidget>
#include "mainwindow.h"
#include "gameScene.h"
#include <QGraphicsView>
#include <QPixMap>
#include "scoredb.h"
#include <QCoreApplication>
#include <QFile>
#include <QDebug>
namespace Ui {
class GameForm;
}

class GameForm : public QWidget
{
    Q_OBJECT
    MainWindow User;

public:
    explicit GameForm(MainWindow::User *userInfo,QWidget *parent = nullptr);
    ~GameForm();
    QString playerName;
    void addUserInfo(MainWindow::User *userData);
    bool isBirthday(QString birthdate);

private slots:
    void on_playBtn_clicked();


    void on_pushButton_clicked();

private:
    Ui::GameForm *ui;
};

#endif // GAMEFORM_H
