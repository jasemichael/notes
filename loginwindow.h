#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QVBoxLayout>

class LoginWindow : public QMainWindow {
    Q_OBJECT
public:
    LoginWindow();
    ~LoginWindow();

private slots:
    void login();

private:
    QLineEdit *usernameLineEdit = new QLineEdit;
    QLineEdit *passwordLineEdit = new QLineEdit;
    QVBoxLayout *layout = new QVBoxLayout();
};
#endif // LOGINWINDOW_H
