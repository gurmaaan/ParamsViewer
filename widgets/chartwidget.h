#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QColorDialog>
#include <QtCharts>
#include <QAbstractAxis>
#include <QPixmap>
#include "services.h"

namespace Ui {
class CHartWidget;
}

class ChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChartWidget(QWidget *parent = nullptr);
    ~ChartWidget();
    inline QStandardItemModel *model() const { return model_; }
    inline QColor color() const { return color_; }
    inline int xColNum() const { return xColNum_; }
    inline int yColNum() const { return yColNum_; }
    inline QVector<double> xValsVec() const { return xValsVec_; }
    inline QVector<double> yValsVec() const { return yValsVec_; }
    inline QString lineName() const { return lineName_; }

signals:
    void xIndexChanged(int x);
    void yIndexChanged(int y);
    void colorChanged(QColor newClr);
    void updateChart(int xCol, int yCol, QColor newColor);

public slots:
    void setModel(QStandardItemModel* model);
    void setCBMaximum(int colCnt);
    void setColor(const QColor &clr);
    void setXColNum(int xColNum);
    void setYColNum(int yColNum);
    void setXValsVec(const QVector<double> &xValsVec);
    void setYValsVec(const QVector<double> &yValsVec);
    void setLineName(const QString &lineName);
    void setDefaultLineName(const QString &function, const QString &argument);

private slots:
    void on_yCB_currentIndexChanged(int index);
    void on_xCB_currentIndexChanged(int index);
    void on_buildBtn_clicked();
    void on_colorBtn_clicked();
    void on_lineNameLE_textChanged(const QString &arg1);

private:
    Ui::CHartWidget *ui;
    QStandardItemModel *model_;

    QChart *chart_;
    QChartView *chartView_;
    QLineSeries *lineSeries_;
    QVXYModelMapper *mapper_;
    void initChart();

    QColor color_;
    QString lineName_;
    int xColNum_;
    int yColNum_;
    QVector<double> xValsVec_;
    QVector<double> yValsVec_;

    QAbstractAxis *generateAxisX();
    QAbstractAxis *generateAxisY();

};

#endif // CHARTWIDGET_H
