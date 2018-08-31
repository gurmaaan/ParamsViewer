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
    bulkWindow_ = new BulkUtilityDialog();
    chartW_ = ui->chartWidget;
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

void MainWindow::scrollToCol(int colNum)
{
    ui->firstFileTableView->scrollTo(ui->firstFileTableView->model()->index(0, colNum));
}

void MainWindow::selectChartCols(int xColNum, int yColNum, QColor color)
{
    QStandardItemModel* m = imOF_->model();
    ItemsService::makeAllItemBGColor(m, QColor(Qt::white));

    scrollToCol(xColNum);

    for(int r = 0; r < m->rowCount(); r++)
    {
        ItemsService::changeBgColor( m->item(r, xColNum), color);
        ItemsService::changeBgColor( m->item(r, yColNum), color);
    }
}

void MainWindow::on_addFileBtn_clicked()
{
    //TODO:: implement me
    ui->addFileAct->trigger();
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
    connect(ui->fileWidget, &FileWidget::fileTextChanged,
            imOF_, &ImageObjectsFile::loadCSVText);
    connect(ui->fileWidget, &FileWidget::filePathChanged,
            imOF_, &ImageObjectsFile::setFilePath);

    connect(ui->fileWidget, &FileWidget::fileRowsCntChanged,
            this, &MainWindow::setAllUIElemntsRowCnt);
    connect(ui->fileWidget, &FileWidget::fileColsCntChanged,
            this, &MainWindow::setAllUIElemntsColCnt);

    connect(imOF_, &ImageObjectsFile::modelChenged,
            ui->firstFileTableView, &QTableView::setModel);
    connect(imOF_, &ImageObjectsFile::modelChenged,
            chartW_, &ChartWidget::setModel);
    connect(imOF_, &ImageObjectsFile::rowProccessed,
            ui->fileWidget, &FileWidget::setProgress);

    connect(chartW_, &ChartWidget::updateChart,
            this, &MainWindow::selectChartCols);
    connect(chartW_, &ChartWidget::xIndexChanged,
            this, &MainWindow::scrollToCol);
    connect(chartW_, &ChartWidget::yIndexChanged,
            this, &MainWindow::scrollToCol);
}

void MainWindow::initUI()
{
    QHeaderView *hH = ui->firstFileTableView->horizontalHeader();
    hH->resetDefaultSectionSize();
    hH->setTextElideMode(Qt::ElideNone);
    hH->resizeSections(QHeaderView::ResizeToContents);
    hH->setSectionResizeMode(QHeaderView::Interactive);
    hH->setSortIndicatorShown(false);

    QHeaderView *vH = ui->firstFileTableView->verticalHeader();
    vH->setAlternatingRowColors(true);
    vH->setSectionResizeMode(QHeaderView::Stretch);
    vH->setSectionResizeMode(QHeaderView::Interactive);

    //----------------------------------
    ui->splitter->setSizes( QList<int>({INT_MAX, INT_MAX}) );
}

void MainWindow::on_actionQuit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::setAllUIElemntsColCnt(int colCnt)
{
    //filewidget - инициатор его не меняю
    //modelSize
    ui->sizeModelColSpin->setMaximum(colCnt);
    ui->sizeModelColSpin->setValue(colCnt);
    //ImageObjectsFile
    imOF_->setColInFileCnt(colCnt);
    //chartView
    ui->chartWidget->setCBMaximum(colCnt);

}

void MainWindow::setAllUIElemntsRowCnt(int rowCnt)
{
    //filewidget - инициатор его не меняю
    //modelSize
    ui->sizeModelRowSpin->setMaximum(rowCnt);
    ui->sizeModelRowSpin->setValue(rowCnt);
    //ImageObjectsFile
    imOF_->setRowInFileCnt(rowCnt);
    //chartView - не важно, берем у модели
}

void MainWindow::on_addFileAct_triggered()
{
    bulkWindow_->show();
}
