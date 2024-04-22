// #ifndef UI_H
// #define UI_H

// #include <QtWidgets>
// #include <QWidget>

// class UI : public QWidget
// {
//     Q_OBJECT

// public:
//     UI(QWidget *parent = nullptr);

// private:
//     // Member variables to store pointers to input fields/widgets
//     QLineEdit *firstNameLineEdit;
//     QLineEdit *lastNameLineEdit;
//     QDateEdit *birthdateEdit;
//     QRadioButton *maleRadioButton;
//     QRadioButton *femaleRadioButton;
//     QLineEdit *userNameLineEdit;
//     QLineEdit *passwordLineEdit;

//     // Forward declaration of user struct
//     struct user;

//     // Method to extract data from input fields and populate user struct
//     user createUserFromInput();

// private slots:
//     void onSignUpButtonClicked();

// private:
//     struct user {
//         QString firstName;
//         QString lastName;
//         QString birthdate;
//         QString gender;
//         QString userName;
//         QString password;
//         QString profileImage;
//     };
// };

// #endif // UI_H
