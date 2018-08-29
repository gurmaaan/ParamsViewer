#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>

#include "model/imageobjectsfile.h"

extern const int _MSG_TIME_;
extern const QString _GURMAAAN_;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_addFileBtn_clicked();

private:
    Ui::MainWindow *ui;
    void applyScreenSettings();
};

#endif // MAINWINDOW_H
