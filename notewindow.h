#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H

#include <QMainWindow>

class NoteWindow : public QMainWindow
{
    Q_OBJECT

public:
    NoteWindow(QString username, QString password);
    ~NoteWindow();

private:
    QString username;
    QString password;
};
#endif // NOTEWINDOW_H
