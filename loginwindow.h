#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QtWidgets>
#include <QtNetwork>
#include <iostream>

class LoginWindow : public QWidget {
    Q_OBJECT

public:
    LoginWindow();
    ~LoginWindow();
    void keyPressEvent(QKeyEvent *e);

private slots:
    void login();

private:
    QLineEdit *usernameLineEdit = new QLineEdit;
    QLineEdit *passwordLineEdit = new QLineEdit;
    QVBoxLayout *layout = new QVBoxLayout();
};
#endif // LOGINWINDOW_H
