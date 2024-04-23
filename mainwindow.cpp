/**Class to handle log in window, and checking login credentials.
 *
 *
 *
 *
 */


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "signupform.h"
#include "gameform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     existingUsers = readExistingUsers();

    // Create an instance of SignUpForm and pass the existingUserNames set
    SignUpForm *signupForm = new SignUpForm(existingUserNames);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/**Button to push user to sign up window.
 *
 */
void MainWindow::on_pushButton_2_clicked()
{
    SignUpForm *signUpForm = new SignUpForm();
    signUpForm->show();
    this->close();
}

/**login button that validates credentials.
 *
 */

void MainWindow::on_LoginBtn_clicked()
{
    if(isUser(ui->username->text(), ui->password->text())){
        User *getUser = new User();
        foreach(User *user, existingUsers){
            if(user->userName == ui->username->text())
                getUser = user;
        }
        //push the user to the gameform screen if successful login.
        GameForm *game = new GameForm(getUser);
        game->show();
        this->close();
        }
    ui->ErrorBox->append("The user does not exist! Please check your username and password.");
    return;
}

/**
 * @brief Method to confirm the user exists.
 * @param user - user to check
 * @param password - password to check
 * @return - bool of if user and password match
 */

bool MainWindow::isUser(const QString& user, const QString& password){
    return existingUserNames.contains(user) && existingUserPassWord.contains(password);
}

/**
 * @brief Read existing users from file to check login credentials
 */
QSet<MainWindow::User *> MainWindow::readExistingUsers()

{
     QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
    // Clear existing usernames to avoid duplicates
    existingUsers.clear();

    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString firstName;
        QString lastName;
        QString birthdate;
        QString gender;
        QString username;
        QString password;
        QString profileImage;
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.startsWith("Username:")) {
                username = line.mid(10).trimmed();
                existingUserNames.insert(username);
            }
            if (line.startsWith("Password:")) {
                password = line.mid(10).trimmed();
                existingUserPassWord.insert(password);
            }

            if (line.startsWith("Birthdate:")) {
                birthdate = line.mid(11).trimmed();
            }

            if (line.startsWith("Last Name:")) {
                lastName = line.mid(11).trimmed();
            }

            if (line.startsWith("First Name:")) {
                firstName = line.mid(12).trimmed();
            }

            if (line.startsWith("Gender:")) {
                gender = line.mid(8).trimmed();
            }

            if (line.startsWith("Profile Image:")) {
                profileImage = line.mid(15).trimmed();
            }


            if(line.isEmpty()){

            User *newUser = new User();
             // Print or process the extracted data
                newUser->firstName = firstName;
                newUser->lastName = lastName;
                newUser->birthdate = birthdate;
                newUser->gender =  gender;
                newUser->userName = username;
                newUser->password = password;
                newUser->profileImage = profileImage;


            // Insert the username into the set
                existingUsers.insert(newUser);
            }

        }
        file.close();
    }
    return existingUsers;
}

/**
 * @brief Button to handle guest user login.
 */
void MainWindow::on_pushButton_clicked()
{
    User *guestUser = new User();
    guestUser->userName = "Guest";
    GameForm *game = new GameForm(guestUser);
    game->show();
    this->close();
}

