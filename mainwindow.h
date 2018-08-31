#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScreen>
#include <QtDebug>
#include "services.h"
#include "model/imageobjectsfile.h"
#include "widgets/bulkutilitydialog.h"

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

public slots:
    void messageResiver(QString message);

private slots:
    void on_addFileBtn_clicked();
    void on_addFileAct_triggered();
    void on_actionQuit_triggered();
    void setAllUIElemntsColCnt(int colCnt);
    void setAllUIElemntsRowCnt(int rowCnt);

private:
    Ui::MainWindow *ui;
    void applyScreenSettings();
    ImageObjectsFile *imOF_;
    BulkUtilityDialog *bulkWindow;
    void connectAll();
    void initUI();
};

#endif // MAINWINDOW_H
