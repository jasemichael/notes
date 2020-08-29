#include "notewindow.h"
#include "loginwindow.h"
#include "viewnote.h"

NoteWindow::NoteWindow(QString username, QString password) {
    this->username = username;
    this->password = password;
    QWidget *window = new QWidget();
    QLabel *userLabel = new QLabel("Welcome " + username + "!");
    userLabel->setStyleSheet("QLabel {font-size: 20pt;}");
    QLabel *menuLabel = new QLabel(tr("Notes"));
    menuLabel->setStyleSheet("QLabel {font-size: 16pt;}");
    QPushButton *createNoteButton = new QPushButton("Create Note");
    layout->addWidget(userLabel);
    layout->addWidget(menuLabel);

    QJsonObject jsonObj;
    jsonObj.insert("username", QJsonValue::fromVariant(username));
    jsonObj.insert("password", QJsonValue::fromVariant(password));
    QJsonDocument doc(jsonObj);

    QNetworkRequest request(QUrl("https://jasemwilson.com/api/get-notes"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkAccessManager man;
    QNetworkReply *reply = man.post(request, doc.toJson());

    while(!reply->isFinished()){
        qApp->processEvents();
    }
    QByteArray resBytes = reply->readAll();
    *data = QJsonDocument::fromJson(resBytes).array();
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openNote(QListWidgetItem*)));
    for(int i = 0; i < data->size(); i++){
        new QListWidgetItem(data->at(i).toObject().value("title").toString(), list);
    }
    layout->addWidget(list);
    layout->addWidget(createNoteButton);
    window->setLayout(layout);
    setCentralWidget(window);
    setWindowTitle(username + QString("'s Notes"));

}

NoteWindow::~NoteWindow(){
}

void NoteWindow::openNote(QListWidgetItem* note){
    for(int i = 0; i < list->count(); i++){
        if(list->item(i) == note){
            ViewNote *note = new ViewNote(data->at(i).toObject());
            note->show();
        }
    }
}
