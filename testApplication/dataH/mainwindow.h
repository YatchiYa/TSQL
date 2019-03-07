#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "includes.h"

QT_FORWARD_DECLARE_CLASS(QPushButton)
QT_FORWARD_DECLARE_CLASS(QTextEdit)


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual~MainWindow();


public slots:

    void on_ExecButton_clicked();
    void on_clearButton_clicked();

private slots:
    void on_ASTButton_clicked();
    void on_loadButton_clicked();

    void on_parserTest_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    // use bouton in mainwindows.cpp
};


#endif // MAINWINDOW_H
