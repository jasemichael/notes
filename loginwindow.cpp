#include "loginwindow.h"
#include "notewindow.h"

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QApplication>

LoginWindow::LoginWindow(){
    QWidget *window = new QWidget();
    QLabel *usernameLabel = new QLabel(tr("Username"));
    QLabel *passwordLabel = new QLabel(tr("Password"));
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    QPushButton *submitButton = new QPushButton(tr("Submit"));
    connect(submitButton, SIGNAL(released()), this, SLOT(login()));
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameLineEdit);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordLineEdit);
    layout->addWidget(submitButton);
    window->setLayout(layout);
    setCentralWidget(window);
    setWindowTitle(tr("Login"));
}

LoginWindow::~LoginWindow(){
    delete this;
}

void LoginWindow::login(){
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    QJsonObject jsonObj;
    jsonObj.insert("username", QJsonValue::fromVariant(username));
    jsonObj.insert("password", QJsonValue::fromVariant(password));

    QJsonDocument doc(jsonObj);

    QNetworkRequest request(QUrl("https://jasemwilson.com/api/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager man;
    QNetworkReply *reply = man.post(request, doc.toJson());

    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QByteArray resBytes = reply->readAll();
    if (resBytes == "True"){
        QLabel *success = new QLabel(tr("Login successful!"));
        success->setStyleSheet("QLabel {background-color: green; color: white;}");
        layout->insertWidget(0, success);
        NoteWindow *note = new NoteWindow(username, password);
        note->show();
        this->close();
    } else {
        QLabel *error = new QLabel(tr("Username or password is incorrect!"));
        error->setStyleSheet("QLabel {background-color: red; color: white;}");
        layout->insertWidget(0, error);
    }


}
