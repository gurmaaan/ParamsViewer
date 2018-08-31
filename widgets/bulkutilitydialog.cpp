#include "bulkutilitydialog.h"
#include "ui_bulkutilitydialog.h"

BulkUtilityDialog::BulkUtilityDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BulkUtilityDialog)
{
    ui->setupUi(this);
}

BulkUtilityDialog::~BulkUtilityDialog()
{
    delete ui;
}
