#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>
#include <QSet>
#include <QRegularExpression>
#include <QDialog>
#include <QGridLayout>
#include <QTextEdit>
#include "mainWindow.h"

namespace Ui {
class SignUpForm;
}

class SignUpForm : public QWidget {
    Q_OBJECT

public:
    struct User {
        QString firstName;
        QString lastName;
        QString birthdate;
        QString gender;
        QString userName;
        QString password;
        QString profileImage;
    };

    explicit SignUpForm(const QSet<QString>& existingUsernames = {}, QWidget *parent = nullptr);
    ~SignUpForm();

    bool isStrongPassword(const QString& password);
    void saveImage(QImage &image, const QString &filePath);

private slots:
    void on_signUp_Submit_clicked();
    void onUploadPictureButtonClicked();
    bool isUnique(const QString& username);
    void readExistingUsernames(QSet<QString>& existingUsernames);




private:
    Ui::SignUpForm *ui;
    QSet<QString> existingUsernames;
    QString pictureName;
    QSet<MainWindow::User *> existingUsers;
    QImage imageObject;
};

#endif // SIGNUPFORM_H
