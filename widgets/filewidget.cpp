#include "filewidget.h"
#include "ui_filewidget.h"

FileWidget::FileWidget(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);

    name_ = "File ";
    path_ = QDir::currentPath();
    type_ = FileType::Dir;
    rowCnt_ = 0;
    colCnt_ = 0;
    progress_= 0;
}

FileWidget::~FileWidget()
{
    delete ui;
}



void FileWidget::setName(const QString &name)
{
    name_ = name;
    setTitle(name_);
}



void FileWidget::setPath(const QString &path)
{
    path_ = path;
    ui->pathLineEdit->setText(path);
    setName(FileService::fileName(path));

    if(FileService::fileExtension(path) == "csv")
        setType(FileType::CSV);

    else
    {
        //TODO:: месадж бокс ошибки если юзер выбрал не тот файл и запуск открытия по новой
        //open error msg box
        //reopen file
    }
}



void FileWidget::setType(const FileType &type)
{
    type_ = type;
    ui->typeCB->addItem(FileService::fileTypeStr(type_));
}



void FileWidget::setRowCnt(int rowCnt)
{
    //current row
    rowCnt_ = rowCnt;
    ui->sizeRowSpin->setValue(rowCnt);
}



void FileWidget::setColCnt(int colCnt)
{
    colCnt_ = colCnt;
    ui->sizeColSpin->setMaximum(colCnt);
    ui->sizeColSpin->setValue(colCnt);
}



void FileWidget::setProgress(int currentRow)
{
    progress_ = currentRow;
    ui->progressBar->setValue(currentRow);
}

void FileWidget::setMaxProgress(int totalFileRowsCnt)
{
    //totalFileRowsCnt = всего строк, когда в др методах текущая строка
    ui->sizeRowSpin->setMaximum(totalFileRowsCnt);
    ui->progressBar->setMaximum(totalFileRowsCnt - 1);
}

void FileWidget::on_pathBtn_clicked()
{
    QString fp = FileService::initDialogAndGetOpenedFileName(Msg::header(MessageType::SelectFile), FileType::CSV);
    setPath(fp);
    emit filePathChenged(fp);
}
