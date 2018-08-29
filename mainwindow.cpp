#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    applyScreenSettings();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_addFileBtn_clicked()
{
    //TODO:: implement me
    //Вставить новый виджет в layOut
    //Вставить таб с таблицей
    //Активировать сравнялку
}

void MainWindow::applyScreenSettings()
{
    QList<QScreen *> scrns = QGuiApplication::screens();
    QRect sR = (scrns.count() > 1) ? scrns.last()->geometry() : scrns.first()->geometry();
    setGeometry(sR);
    showMaximized();
}
