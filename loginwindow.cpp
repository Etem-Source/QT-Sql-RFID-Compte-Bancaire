#include "loginwindow.h"
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QScreen>
#include <QApplication>
#include <QSerialPort> // sudo apt-get install libqt5serialport5-dev
#include <QSerialPortInfo>


LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Connexion");
    resize(400, 300);
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Connexion à votre compte", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    cinEdit = new QLineEdit(this);
    cinEdit->setPlaceholderText("CIN");
    cinEdit->setReadOnly(true);
    layout->addWidget(cinEdit);

    codeSecretEdit = new QLineEdit(this);
    codeSecretEdit->setPlaceholderText("Code Secret");
    codeSecretEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(codeSecretEdit);

    showPasswordCheckBox = new QCheckBox("Afficher le code secret", this);
    layout->addWidget(showPasswordCheckBox);
    connect(showPasswordCheckBox, &QCheckBox::stateChanged, this, &LoginWindow::togglePasswordVisibility);

    loginButton = new QPushButton("Connexion", this);
    layout->addWidget(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::login);

    setLayout(layout);

    // Centrer la fenêtre
    centerWindow();

    setupSerialPort();
}

void LoginWindow::centerWindow()
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void LoginWindow::togglePasswordVisibility()
{
    if (showPasswordCheckBox->isChecked()) {
        codeSecretEdit->setEchoMode(QLineEdit::Normal);
    } else {
        codeSecretEdit->setEchoMode(QLineEdit::Password);
    }
}

void LoginWindow::login()
{
    QString cin = cinEdit->text();
    QString codeSecret = codeSecretEdit->text();

    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen())
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("localhost");
        db.setDatabaseName("QTBDD");
        db.setUserName("qtsql");
        db.setPassword("Qtsql?99");

        if (!db.open()) {
            QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée: " + db.lastError().text());
            return;
        }
    }

    QSqlQuery query;
    query.prepare("SELECT cl.id, cl.nom, cl.prenom FROM clients cl JOIN comptes c ON cl.compte_id = c.id WHERE cl.cin = :cin AND c.code_secret = :code_secret");
    query.bindValue(":cin", cin);
    query.bindValue(":code_secret", codeSecret);

    if (!query.exec()) {
        qDebug() << "Erreur d'exécution de la requête: " << query.lastError().text();
        QMessageBox::critical(this, "Erreur", "Erreur d'exécution de la requête: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        int clientId = query.value(0).toInt();
        QString nom = query.value(1).toString();
        QString prenom = query.value(2).toString();

        MainWindow *mainWindow = new MainWindow(clientId);
        mainWindow->show();
        this->close();
    } else {
        loginButton->setStyleSheet("QPushButton { background-color: #ff0000; }"); // Rouge
        QMessageBox::warning(this, "Erreur", "CIN ou Code Secret incorrect");
        loginButton->setStyleSheet("QPushButton { background-color: #4CAF50; }"); // Vert
    }
}

void LoginWindow::setupSerialPort() {
    serial = new QSerialPort(this);

    // Recherche des ports disponibles
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Port détecté :" << info.portName();
        serial->setPort(info); // Teste chaque port
        if (serial->open(QIODevice::ReadOnly)) {
            qDebug() << "Connexion réussie avec :" << info.portName();
            break;
        } else {
            qDebug() << "Échec de connexion avec :" << info.portName();
        }
    }

    // Paramétrage de la communication série
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    // Vérification si le port série est ouvert
    if (serial->isOpen()) {
        qDebug() << "Le port série est ouvert et prêt à recevoir des données.";
        connect(serial, &QSerialPort::readyRead, this, &LoginWindow::readSerialData);
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le port série : " + serial->errorString());
    }
}

void LoginWindow::readSerialData() {
    while (serial->canReadLine()) {  // Vérifie si une ligne complète est disponible
        QByteArray data = serial->readLine().trimmed();  // Lit une ligne

        qDebug() << "Données reçues :" << data;  // Affiche les données dans le terminal de débogage

        // Vérifiez si les données ne sont pas vides
        if (!data.isEmpty()) {
            // Convertir la ligne en une chaîne de caractères sans espaces
            QString uid = QString::fromUtf8(data).toUpper();  // .simplified() pour retirer les espaces excédentaires

            qDebug() << "UID reçu dans le format : " << uid;  // Affiche l'UID reçu

            // Mettre à jour le champ CIN avec l'UID
            cinEdit->setText(uid);
        }
    }
}

/*
UID de la carte : BC 8B A4 3D (Bleu) (Etem)
UID de la carte : A 77 A4 3D (Noir) (Corentin)
UID de la carte : D DB A4 3D (Jaune) (Luka)
 */

