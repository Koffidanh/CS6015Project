#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>
#include <QSet> // Include the header for QSet
#include <QRegularExpression>
#include <Qdialog>
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
    explicit SignUpForm(QWidget *parent = nullptr);
    ~SignUpForm();
    bool isStrongPassword(const QString& password);
    void saveImage(QPixmap &image, QString &filePath);

private slots:
    void on_pushButton_4_clicked();
    void onUploadPictureButtonClicked();
    bool isUnique(const QString& username);
    void readExistingUsernames();

private:
    Ui::SignUpForm *ui;
    QSet<QString> existingUsernames;
    QString pictureName;
};

#endif // SIGNUPFORM_H
