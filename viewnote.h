#ifndef VIEWNOTE_H
#define VIEWNOTE_H

#include <QMainWindow>
#include <QJsonObject>

class ViewNote : public QMainWindow {
    Q_OBJECT

public:
    ViewNote(QJsonObject note);
    ~ViewNote();

signals:

private:

};

#endif // VIEWNOTE_H
