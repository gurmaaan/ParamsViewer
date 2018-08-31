#include "chartwidget.h"
#include "ui_chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CHartWidget)
{
    ui->setupUi(this);
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

QStandardItemModel *ChartWidget::model() const
{
    return model_;
}

void ChartWidget::setModel(QStandardItemModel *model)
{
    model_ = model;
    int colCnt = model_->columnCount();
    setMaximum(colCnt);
    for(int c = 0; c < colCnt; c++)
    {
        QString curCOlName = model_->headerData(c, Qt::Horizontal, Qt::StatusTipRole).toString();
//        ui->xCB->addItem(curCOlName);
//        ui->yCB->addItem(curCOlName);
        ui->xCB->setModel(model_);
        ui->yCB->setModel(model_);
    }
}

void ChartWidget::setMaximum(int colCnt)
{
    ui->allXColSB->setMaximum(colCnt);
    ui->allXColSB->setValue(colCnt);
    ui->curXColSB->setMaximum(colCnt);

    ui->allYColSB->setMaximum(colCnt);
    ui->allYColSB->setValue(colCnt);
    ui->curYColSB->setMaximum(colCnt);
}
