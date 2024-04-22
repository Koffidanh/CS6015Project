/** Class to handle the sign up form, and managing the database of users.
 *
 *
 *
*/

#include "signupform.h"
#include "ui_signupform.h"
#include <QFileDialog>
#include <QTextStream>

SignUpForm::SignUpForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SignUpForm)
    , existingUsernames()
{
    ui->setupUi(this);
    // Connect the submit button click signal to the slot
    connect(ui->signUp_Submit, &QPushButton::clicked, this, &SignUpForm::on_pushButton_4_clicked);
    // Connect the upload picture button click signal to a slot
    connect(ui->signUp_UploadPicture, &QPushButton::clicked, this, &SignUpForm::onUploadPictureButtonClicked);

    // Read existing usernames from the file when the form is constructed
    readExistingUsernames();

}

SignUpForm::~SignUpForm()
{
    delete ui;
}

/**Method to handle validating, and pushing sign up data to database textfile.
 * @brief SignUpForm::on_pushButton_4_clicked
 */
void SignUpForm::on_pushButton_4_clicked()

{
    QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
    // Get the username entered by the user
    QString username = ui->signUp_UserName->text().trimmed();

    if (username.isEmpty()) {
        ui->testresult->setText("Error: Please enter a username!");
        return;
    }

    if (isUnique(username)) {

        //Take the user input from the form and add it to a struct to push to the database file.
        User newUser;
        newUser.firstName = ui->signUp_FirstName->text();
        newUser.lastName = ui->signUp_LastName->text();
        newUser.birthdate = ui->signUp_DateBirth->date().toString("yyyy-MM-dd");
        newUser.gender = ui->signUp_Male->isChecked() ? "Male" : "Female";
        newUser.userName = username;
        QString passwordCheck = ui->signUp_PassWord->text();


        //ensure password matches check criteria.
        if (!isStrongPassword(passwordCheck) || passwordCheck.length() < 8) {
            ui->testresult->setText("Error: Password must contain at least one uppercase letter, one lowercase letter, one digit, and be at least 8 characters long!");
            return;
        }

        newUser.password = ui->signUp_PassWord->text();

        newUser.profileImage = pictureName;


        // Write user data to a database
        QFile file(filePath);
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << "First Name: " << newUser.firstName << "\n"
                << "Last Name: " << newUser.lastName << "\n"
                << "Birthdate: " << newUser.birthdate << "\n"
                << "Gender: " << newUser.gender << "\n"
                << "Username: " << newUser.userName << "\n"
                << "Password: " << newUser.password << "\n"
                << "Profile Image: " << newUser.profileImage << "\n\n";
            file.close();

            // Add the new username to the set of existing usernames
            existingUsernames.insert(username);

            //Populate a successful sign up window and send user to log in.
            QDialog *confirmation = new QDialog();
            QGridLayout *gridConfirm = new QGridLayout(confirmation);
            QTextEdit *success = new QTextEdit("Signup Confirmed");
            QPushButton *confirmButton = new QPushButton("Accept");
            gridConfirm->addWidget(success,0,10);
            gridConfirm->addWidget(confirmButton,0,30);
            connect(confirmButton, &QPushButton::clicked, confirmation, &QDialog::accept);
            while(!confirmation->exec()==QDialog::Accepted){

            }
            MainWindow *newView = new MainWindow();
            newView->show();
            this->close();

        } else {
            ui->testresult->setText("Error: Unable to open file for writing.");
        }
    } else {
        ui->testresult->setText("Error: Please enter a unique username!");
    }
}

/** Method to handle button press to upload a image file for the user profile.
 * @brief SignUpForm::onUploadPictureButtonClicked
 */
void SignUpForm::onUploadPictureButtonClicked()
{
    // Open a file dialog to select a picture
    QString pictureFileName = QFileDialog::getOpenFileName(this, tr("Open Picture"), "", tr("Image Files (*.png *.jpg *.jpeg *.bmp)"));

    // Check if a file was selected
    if (!pictureFileName.isEmpty()) {
        // Extract the file name from the full path
        QFileInfo fileInfo(pictureFileName);
        pictureName = fileInfo.fileName();
    }
}

/**Method to ensure username doesn't already exist
 * @brief SignUpForm::isUnique
 * @param username - username to check in list
 * @return boolean of if username found.
 */
bool SignUpForm::isUnique(const QString& username)
{
    return !existingUsernames.contains(username);
}

/**Method to read in database of usernames.
 * @brief SignUpForm::readExistingUsernames
 */

void SignUpForm::readExistingUsernames()

{
    QString filePath = QCoreApplication::applicationDirPath() + "/users.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        //read file until we hit the end.
        while (!in.atEnd()) {
            QString line = in.readLine();
            //pull out username
            if (line.startsWith("Username:")) {
                QString username = line.mid(10).trimmed(); // Extract the username
                existingUsernames.insert(username);
            }
        }
        file.close();
    }
}

/**Method to check if password meets the expected criteria.
 *
 * @param password - password to check
 * @return - bool of if password meets criteria.
 */

bool SignUpForm::isStrongPassword(const QString& password) {
    // Check if the password contains at least one uppercase letter, one lowercase letter,
    // one digit, and is at least 8 characters long
    QRegularExpression regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
    return regex.match(password).hasMatch();
}

/**Method to save image to a location.
 *
 * @param image to save
 * @param filePath to save image to
 */
void SignUpForm::saveImage(QPixmap &image, QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly)) {
        image.save(&file, "PNG");
        file.close();
    } else {
        qDebug() << "Failed to save image to" << filePath;
    }
}
