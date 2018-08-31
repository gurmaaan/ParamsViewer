#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QAbstractItemView>

namespace Ui {
class CHartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    ~ChartWidget();

    QStandardItemModel *model() const;

public slots:
    void setModel(QStandardItemModel* model);
    void setCBMaximum(int colCnt);

private:
    Ui::CHartWidget *ui;
    QStandardItemModel *model_;
};

#endif // CHARTWIDGET_H
