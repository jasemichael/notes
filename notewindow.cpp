#include "notewindow.h"
#include "loginwindow.h"
#include "ui_notewindow.h"
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QPushButton>
#include <QDebug>
#include <iostream>

NoteWindow::NoteWindow(QString username, QString password) {
    this->username = username;
    this->password = password;
    QWidget *window = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *userLabel = new QLabel("Welcome " + username + "!");
    userLabel->setStyleSheet("QLabel {font-size: 20pt;}");
    QLabel *menuLabel = new QLabel(tr("Notes"));
    menuLabel->setStyleSheet("QLabel {font-size: 16pt;}");
    QPushButton *createNoteButton = new QPushButton("Create Note");
    layout->addWidget(userLabel);
    layout->addWidget(menuLabel);
    layout->addWidget(createNoteButton);

    QJsonObject jsonObj;
    jsonObj.insert("username", QJsonValue::fromVariant(username));
    jsonObj.insert("password", QJsonValue::fromVariant(password));
    QJsonDocument doc(jsonObj);

    QNetworkRequest request(QUrl("http://127.0.0.1:8000/api/get-notes"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager man;
    QNetworkReply *reply = man.post(request, doc.toJson());

    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QByteArray resBytes = reply->readAll();
    QJsonDocument itemDoc = QJsonDocument::fromJson(resBytes);
    for(int i = 0; i < itemDoc.size(); i++){
        qDebug() << itemDoc[i];
    }
    qDebug() << itemDoc;
    window->setLayout(layout);
    setCentralWidget(window);

}

NoteWindow::~NoteWindow(){
}

