#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct User {
        QString firstName;
        QString lastName;
        QString birthdate;
        QString gender;
        QString userName;
        QString password;
        QString profileImage;

    };
     QSet<User*> readExistingUsers();

private slots:
    void on_pushButton_2_clicked();

    void on_LoginBtn_clicked();

    bool isUser(const QString& user, const QString& password);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSet<User*> existingUsers;
    QSet<QString> existingUserNames;
    QSet<QString> existingUserPassWord;
};
#endif // MAINWINDOW_H
