// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printer)
#if QT_CONFIG(printdialog)
#include <QPrintDialog>
#endif // QT_CONFIG(printdialog)
#include <QPrinter>
#endif // QT_CONFIG(printer)
#endif // QT_PRINTSUPPORT_LIB
#include <QFont>
#include <QFontDialog>
#include<string>
#include "notepad.h"
#include<QTimer>
#include<QMessageBox>
#include "ui_notepad.h"
#include <QVBoxLayout>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextDocument>
#include <QRegularExpression>
#include <QPainter>
#include <QDebug>
#include <QString>
#include <QTextEdit>
#include<QProcess>
#include <fstream>
#include <vector>
#include <sstream>
#include <QPalette>
#include<QMap>
#include <QTextEdit>
#include <QString>
#include <QList>
#include <QPair>
#include <QFile>
#include <QTextStream>
#include<iostream>
#include<vector>
#include<fstream>
#include <sstream>
#include <string>
#include <cctype>
#include<algorithm>


Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);

    connect(ui->actionNew, &QAction::triggered, this, &Notepad::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &Notepad::open);
    connect(ui->actionSave, &QAction::triggered, this, &Notepad::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &Notepad::saveAs);
    connect(ui->actionPrint, &QAction::triggered, this, &Notepad::print);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
#if QT_CONFIG(clipboard)
    connect(ui->textEdit, &QTextEdit::copyAvailable, ui->actionCopy, &QAction::setEnabled);
    connect(ui->actionCopy, &QAction::triggered, ui->textEdit, &QTextEdit::copy);
    connect(ui->actionCut, &QAction::triggered, ui->textEdit, &QTextEdit::cut);
    connect(ui->actionPaste, &QAction::triggered, ui->textEdit, &QTextEdit::paste);
#endif
    connect(ui->textEdit, &QTextEdit::undoAvailable, ui->actionUndo, &QAction::setEnabled);
    connect(ui->actionUndo, &QAction::triggered, ui->textEdit, &QTextEdit::undo);
    connect(ui->textEdit, &QTextEdit::redoAvailable, ui->actionRedo, &QAction::setEnabled);
    connect(ui->actionRedo, &QAction::triggered, ui->textEdit, &QTextEdit::redo);

    connect(ui->actionFont, &QAction::triggered, this, &Notepad::selectFont);
    connect(ui->actionBold, &QAction::triggered, this, &Notepad::setFontBold);
    connect(ui->actionUnderline, &QAction::triggered, this, &Notepad::setFontUnderline);
    connect(ui->actionItalic, &QAction::triggered, this, &Notepad::setFontItalic);
    connect(ui->actionAbout, &QAction::triggered, this, &Notepad::about);

// Disable menu actions for unavailable features
#if !defined(QT_PRINTSUPPORT_LIB) || !QT_CONFIG(printer)
    ui->actionPrint->setEnabled(false);
#endif

#if !QT_CONFIG(clipboard)
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
#endif
}

#include <QTextCursor>
#include<QAction>
#include<QMenu>
#include<QMap>

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::newDocument()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::save()
{
    QString fileName;
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev, this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif // QT_CONFIG(printdialog)
    ui->textEdit->print(&printDev);
#endif // QT_CONFIG(printer)
}

void Notepad::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Notepad::setFontUnderline(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}

void Notepad::setFontItalic(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}

void Notepad::setFontBold(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);
}

void Notepad::about()
{
    QMessageBox::about(this, tr("About Notepad"),
                       tr("The <b>Notepad</b> example demonstrates how to code a basic "
                          "text editor using QtWidgets"));
}
QString text;



QString getToolTip(const QString& word) {
    return "Tooltip for: " + word;
}

bool Notepad::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->textEdit_2 && event->type() == QEvent::MouseButtonPress) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QTextCursor cursor = ui->textEdit_2->cursorForPosition(mouseEvent->pos());
        cursor.select(QTextCursor::WordUnderCursor);
        QString selectedText = cursor.selectedText();

        return true;
    }
    return QWidget::eventFilter(obj, event);
}


QString toTitleCase(const QString &str) { QString result; bool capitalizeNext = true; for (QChar ch : str) { if (ch.isSpace()) { capitalizeNext = true; result += ch; } else if (capitalizeNext) { result += ch.toUpper(); capitalizeNext = false; } else { result += ch.toLower(); } } return result; }

void Notepad::mousePressEvent(QMouseEvent *event) {
    // qDebug()<< "In mouse event\n";
    if (event->button() == Qt::RightButton) {
        QPoint pos = ui->textEdit_2->mapFromGlobal(event->globalPos());
        QTextCursor cursor = ui->textEdit_2->cursorForPosition(pos);
        cursor.select(QTextCursor::WordUnderCursor);
        QString key =cursor.selectedText().toLower();
        QString selectedText = "<center>Selected Word: <strong>"+toTitleCase(key)+"</strong></center>\n"+"<center>Parts Of Speech: "+partSpeech[key]+"</center>\n"+"<center>Meaning: "+meaning[key]+"\n</center>"+"<center>Synonym: "+synonyms[key]+"</center>\n"+"<center>Sentence: "+sentences[key]+"</center>";

        QMessageBox msgBox(ui->textEdit_2);
        msgBox.setWindowTitle("Information");
        msgBox.setText(selectedText);

        msgBox.setStyleSheet("QPushButton "
        "{"
        " border-style: outset;"
        " border-width: 2px;"
        " border-radius: 10px;"
        " border-color: beige;"
        " font: bold 14px;"
        " min-width: 25em;"
        " padding: 6px;"
        "}"
        );
        msgBox.setStandardButtons(QMessageBox::Ok);

        msgBox.exec();
    }
}

void getWordMeaning(const QString &word)
{

    QString program = "python";
    QStringList arguments;

    arguments << "C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/word_lookup.py" << word ;

    QProcess process;
    process.start(program,arguments);
    process.waitForFinished(-1);

    qDebug() <<"Successfully! Done!";

}
void getMappingMeaning(QMap<QString, QString> &map,const QString &filename){

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << file.errorString();
    }

    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();

        if (!line.isEmpty()) {
            int spaceIndex = line.indexOf(' ');
            if (spaceIndex != -1) {
                QString key = line.left(spaceIndex);
                QString value = line.mid(spaceIndex + 1);
                map.insert(key, value);
            }
        }
}
     file.close();
}
void Notepad::on_button_read_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    text = ui->textEdit->toPlainText();
    getWordMeaning(text);
    ui->textEdit_2->installEventFilter(this);
    ui->textEdit_2->setText(text);
    ui->textEdit_2->setContextMenuPolicy(Qt::NoContextMenu);
    QString filename = "C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/synonyms.txt";
    getMappingMeaning(Notepad::synonyms,filename);
    filename = "C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/meanings.txt";
    getMappingMeaning(Notepad::meaning,filename);
    filename = "C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/partsOfSpeech.txt";
    getMappingMeaning(Notepad::partSpeech,filename);
    filename = "C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/examples.txt";
    getMappingMeaning(Notepad::sentences,filename);
}
QString highlightText(const QString& text, const QString& color) {
    return QString("<span style=\"background-color: %1;\">%2</span>").arg(color, text.toHtmlEscaped());
}
void setHighlightedText(QTextEdit* textEdit, const QString& fullText,QMap<int,QString>&map) {

    QString highlightedWords;
    for (int i = 0; i < fullText.size(); i++) {

            highlightedWords.append(highlightText(fullText[i], map[i]));
    }
    QString highlightedText = highlightedWords;
    textEdit->setHtml(highlightedText);
}


void indexToMap(QVector<int> vec,QMap<int,QString>&map,QString str){
    int count=0;
    QString col = "";
    for(int i=0;i<vec.size()-1;i+=2){
        for(int j=vec[i];j<=vec[i+1];j++){
            map[j] = "red";
        }
    }
}
int countWords(const std::string& str) {
    std::istringstream stream(str);
    std::string word;
    int count = 0;

    while (stream >> word) {
        count++;
    }

    return count;
}

void checkPlagiarismFromQt(const QString& text) {

    QString program = "python";
    QStringList arguments;
    arguments << "C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/plagiarism_checker2.py " << text ;


    QProcess process;
    process.start(program, arguments);
    process.waitForFinished(-1);
}
void Notepad::on_button_plag_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);
    QString text = ui->textEdit->toPlainText();
    checkPlagiarismFromQt(text);
    QFile inputFile("C:/Qt/Examples/Qt-6.8.0/widgets/tutorials/notepad/plagiarism_output.txt");
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Unable to open file";
    }

    int words;
    float plagiarism;
    QVector<int> values;
    QTextStream in(&inputFile);
    in >> words;
    in >> plagiarism;
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (!line.isEmpty()) {
            QStringList parts = line.split(" ");
            if (parts.size() >= 2) {
                bool ok1, ok2;
                int a = parts[0].toInt(&ok1);
                int b = parts[1].toInt(&ok2);
                if (ok1 && ok2) {
                    values.append(a);
                    values.append(b);
                }
            }
        }
    }
    qDebug() << "Values:" << values;
    for(auto i:values){
        qDebug()<<i<<" ";
    }
    ui->lineEdit_wordCount->setText(QString::number(words));
    ui->lineEdit_plag->setText(QString::number(plagiarism)+"%");
    QPalette palette = ui->lineEdit_plag->palette();
    QColor customColor(168, 128, 67);
    if(plagiarism<20)
    palette.setColor(QPalette::Base, Qt::darkGreen);
    else if(plagiarism<50)
    palette.setColor(QPalette::Base, customColor);
    if(plagiarism>=50)
    palette.setColor(QPalette::Base, Qt::red);
    ui->lineEdit_plag->setPalette(palette);
    inputFile.close();
    QMap<int,QString> map;
    indexToMap(values,map,text);
    setHighlightedText(ui->textEdit_3,text,map);
}


void Notepad::on_button_plag_2_clicked() {
    ui->stackedWidget->setCurrentIndex(2);
    Notepad::on_button_plag_clicked();
}


void Notepad::on_button_edit_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Notepad::on_button_edit_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Notepad::on_button_read_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    Notepad::on_button_read_clicked();
}


void Notepad::on_pushButton_8_clicked()
{
    std::exit(0);
}


void Notepad::on_pushButton_6_clicked()
{
    std::exit(0);
}


void Notepad::on_pushButton_3_clicked()
{
    std::exit(0);
}



void Notepad::on_button_plag_pressed()
{

}

