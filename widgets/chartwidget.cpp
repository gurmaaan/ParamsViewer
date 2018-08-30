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
}
