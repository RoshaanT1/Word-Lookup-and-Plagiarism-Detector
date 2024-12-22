// Copyright (C) 2018 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef NOTEPAD_H
#define NOTEPAD_H
#include <QMainWindow>
#include <QTextEdit>
#include <QPainter>
#include<QMouseEvent>
#include <QTextCursor>
#include <QTextBlock>
#include <QTextLayout>
#include <QScrollBar>
#include <QRect>
#include <QPoint>
#include <QApplication>
#include <QEvent>
#include <QContextMenuEvent>
#include <QMap>
QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    QMap<QString,QString>synonyms;
    QMap<QString,QString>meaning;
    QMap<QString,QString>partSpeech;
    QMap<QString,QString>sentences;
    ~Notepad();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void newDocument();
    void open();
    void save();
    void saveAs();
    void print();
    void selectFont();
    void setFontBold(bool bold);
    void setFontUnderline(bool underline);
    void setFontItalic(bool italic);
    void about();

    void on_button_read_clicked();

    void on_button_plag_clicked();

    void on_button_plag_2_clicked();

    void on_button_edit_clicked();

    void on_button_edit_2_clicked();

    void on_button_read_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();
    // void handleCursorChange();

    void on_button_plag_pressed();

private:
    Ui::Notepad *ui;
    QString currentFile;
};

#endif // NOTEPAD_H
