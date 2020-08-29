#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QtWidgets>
#include <QtNetwork>
#include <iostream>

class NoteWindow : public QMainWindow {
    Q_OBJECT
public:
    NoteWindow(QString username, QString password);
    ~NoteWindow();

private slots:
    void openNote(QListWidgetItem* note);

private:
    QString username;
    QString password;
    QVBoxLayout *layout = new QVBoxLayout();
    QListWidget *list = new QListWidget();
    QJsonArray *data = new QJsonArray();
};
#endif // NOTEWINDOW_H
