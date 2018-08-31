#include "chartwidget.h"
#include "ui_chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CHartWidget)
{
    ui->setupUi(this);
    model_ = new QStandardItemModel();
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
        setYColNum(index);
}

void ChartWidget::on_xCB_currentIndexChanged(int index)
{
    if(model_->columnCount() != 0)
        setXColNum(index);
}

void ChartWidget::on_buildBtn_clicked()
{
    qDebug() << "X vector count :" << xValsVec_.count();
    qDebug() << "Y vector count :" << yValsVec_.count();
    qDebug() << " ---------------------------";
    qDebug() << "|\tx\t|\ty\t|";
        qDebug() << " ---------------------------";
    for(int r = 0; r < model_->rowCount(); r++)
    {
        qDebug() << "| " << xValsVec_.at(r) << "| " << yValsVec_.at(r) << "| ";
    }
}

void ChartWidget::setColor(const QColor &clr)
{
    color_ = clr;
    QPalette palette = ui->colorLabel->palette();
    palette.setColor(ui->colorLabel->backgroundRole(), color_);
    ui->colorLabel->setPalette(palette);

    emit colorChanged(color_);
}

void ChartWidget::on_colorBtn_clicked()
{
    QColor userSelectedCOlor = QColorDialog::getColor();
    setColor(userSelectedCOlor);
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
