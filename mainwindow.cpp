#include "mainwindow.h"
#include "ui_mainwindow.h"

const int _MSG_TIME_ = 4500;
const QString _GURMAAAN_ = "https://github.com/gurmaaan/ParamsViewer";


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    imOF_ = new ImageObjectsFile();

    applyScreenSettings();
    connectAll();
    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::messageResiver(QString message)
{
    qDebug().noquote() << message;
    ui->statusBar->showMessage(message, _MSG_TIME_);
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

void MainWindow::connectAll()
{
    connect(ui->fileWidget, &FileWidget::filePathChenged,
            imOF_, &ImageObjectsFile::loadCSV);
}

void MainWindow::initUI()
{

}
