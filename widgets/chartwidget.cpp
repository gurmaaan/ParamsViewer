#include "chartwidget.h"
#include "ui_chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CHartWidget)
{
    ui->setupUi(this);
    model_ = new QStandardItemModel();
    setColor(QColor(Qt::white));
    setDefaultLineName("...", "...");
    initChart();
}

ChartWidget::~ChartWidget()
{
    delete ui;
}



void ChartWidget::setModel(QStandardItemModel *model)
{
    model_ = model;
    int colCnt = model_->columnCount();
    setCBMaximum(colCnt);
    for(int c = 0; c < colCnt; c++)
    {
        QString curCOlName = model_->headerData(c, Qt::Horizontal, Qt::StatusTipRole).toString();
        ui->xCB->addItem(curCOlName);
        ui->yCB->addItem(curCOlName);
    }
    setXColNum(0);
    setYColNum(0);
}

void ChartWidget::setCBMaximum(int colCnt)
{
    if(colCnt != ui->allXColSB->maximum())
    {
        ui->allXColSB->setMaximum(colCnt - 1);
        ui->allXColSB->setValue(colCnt - 1);
        ui->curXColSB->setMaximum(colCnt - 1);

        ui->allYColSB->setMaximum(colCnt - 1);
        ui->allYColSB->setValue(colCnt - 1);
        ui->curYColSB->setMaximum(colCnt - 1);
    }
}

void ChartWidget::on_yCB_currentIndexChanged(int index)
{
    if(model_->columnCount() != 0)
    {
        setYColNum(index);
        setDefaultLineName(ui->xCB->itemText(index), ui->yCB->currentText());
    }
}

void ChartWidget::on_xCB_currentIndexChanged(int index)
{
    if(model_->columnCount() != 0)
    {
        setXColNum(index);
        setDefaultLineName(ui->xCB->currentText(), ui->yCB->itemText(index));
    }
}

void ChartWidget::on_buildBtn_clicked()
{
//    qDebug() << "X vector count :" << xValsVec_.count();
//    qDebug() << "Y vector count :" << yValsVec_.count();
//    qDebug() << " ---------------------------";
//    qDebug() << "|\tx\t|\ty\t|";
//        qDebug() << " ---------------------------";
//    for(int r = 0; r < model_->rowCount(); r++)
//    {
//        qDebug() << "| " << xValsVec_.at(r) << "| " << yValsVec_.at(r) << "| ";
//    }

    emit updateChart(ui->xCB->currentIndex(), ui->yCB->currentIndex(), color());
}

void ChartWidget::setColor(const QColor &clr)
{
    color_ = clr;
    QPixmap pm = QPixmap( ui->colorBtn->iconSize());
    pm.fill(clr);
    pm = ImageService::addRect(pm);
    ui->colorBtn->setIcon(QIcon(pm));
    emit colorChanged(color_);
}

void ChartWidget::on_colorBtn_clicked()
{
    QColor userSelectedCOlor = QColorDialog::getColor();
    setColor(userSelectedCOlor);
}

void ChartWidget::initChart()
{
    chart_ = new QChart;
    lineSeries_ = new QLineSeries;
    chartView_ = new QChartView(chart_);
}

void ChartWidget::setLineName(const QString &lineName)
{
    lineName_ = lineName;
}

void ChartWidget::setDefaultLineName(const QString &function, const QString &argument)
{
    QString newName = "Dependence between " + function + " and " + argument;
    qDebug() << newName;
    ui->lineNameLE->setText(newName);
}

void ChartWidget::setYValsVec(const QVector<double> &yValsVec)
{
    yValsVec_ = yValsVec;
}

void ChartWidget::setXValsVec(const QVector<double> &xValsVec)
{
    xValsVec_ = xValsVec;
}

void ChartWidget::setYColNum(int yColNum)
{
    yColNum_ = yColNum;
    emit yIndexChanged(yColNum_);
    if(model_->columnCount() > 0 && model_->columnCount() >= yColNum_)
        setYValsVec(ItemsService::getColVals(model_, yColNum_));
}

void ChartWidget::setXColNum(int xColNum)
{
    xColNum_ = xColNum;
    emit xIndexChanged(xColNum_);
    if(model_->columnCount() > 0 && model_->columnCount() >= xColNum_)
        setXValsVec(ItemsService::getColVals(model_, xColNum_));
}

void ChartWidget::on_lineNameLE_textChanged(const QString &arg1)
{
    setLineName(arg1);
}
