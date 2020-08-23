#include "notewindow.h"
#include "loginwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWindow *login = new LoginWindow();
    //login->show();
    NoteWindow *note = new NoteWindow(QString("jasemichael"), QString("2049812"));
    note->show();
    return a.exec();
}
