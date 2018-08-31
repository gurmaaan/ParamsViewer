#ifndef BULKUTILITYDIALOG_H
#define BULKUTILITYDIALOG_H

#include <QDialog>

namespace Ui {
class BulkUtilityDialog;
}

class BulkUtilityDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BulkUtilityDialog(QWidget *parent = nullptr);
    ~BulkUtilityDialog();

private:
    Ui::BulkUtilityDialog *ui;
};

#endif // BULKUTILITYDIALOG_H
