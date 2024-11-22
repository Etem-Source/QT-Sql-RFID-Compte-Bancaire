#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QSerialPort> // sudo apt-get install libqt5serialport5-dev
#include <QSerialPortInfo>

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);

private slots:
    void login();
    void togglePasswordVisibility();


private:
    QLineEdit *cinEdit;
    QLineEdit *codeSecretEdit;
    QCheckBox *showPasswordCheckBox;
    QPushButton *loginButton;

    void centerWindow();

    QSerialPort *serial; // Pour gérer la communication série
    void setupSerialPort(); // Initialiser le port série
    void readSerialData();
};

#endif // LOGINWINDOW_H
