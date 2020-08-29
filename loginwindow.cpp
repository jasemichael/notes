#include "loginwindow.h"
#include "notewindow.h"

LoginWindow::LoginWindow(){
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
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setAlignment(this, Qt::AlignCenter);
    setLayout(layout);
    setWindowState(Qt::WindowMaximized);
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
        close();
    } else {
        QLabel *error = new QLabel(tr("Username or password is incorrect!"));
        error->setStyleSheet("QLabel {background-color: red; color: white;}");
        layout->insertWidget(0, error);
    }


}

void LoginWindow::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Return){
        login();
    }
}
