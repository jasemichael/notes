#include "viewnote.h"

#include <QLabel>
#include <QtWidgets>

ViewNote::ViewNote(QJsonObject note) {
    QWidget *window = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();
    QLabel *titleLabel = new QLabel(tr("Title"));
    titleLabel->setStyleSheet("QLabel {font-size: 18pt;}");
    QLabel *dateLabel = new QLabel(QString("Created on ") + note.value("date").toString().section("", 0, 10));
    dateLabel->setStyleSheet("QLabel {font-size: 20pt;}");
    QLabel *noteTitleLabel = new QLabel(note.value("title").toString());
    QLabel *contentLabel = new QLabel(tr("Content"));
    contentLabel->setStyleSheet("QLabel {font-size: 18pt;}");
    QLabel *noteContentLabel = new QLabel(note.value("content").toString());
    layout->addWidget(dateLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(noteTitleLabel);
    layout->addWidget(contentLabel);
    layout->addWidget(noteContentLabel);
    window->setLayout(layout);
    setCentralWidget(window);
    setWindowTitle(QString("Note: ") + note.value("title").toString());
}

ViewNote::~ViewNote(){

}
