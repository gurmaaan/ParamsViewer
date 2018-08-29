#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QGroupBox>
#include <QStandardPaths>
#include <services/fileservice.h>
#include <services/stringservice.h>

namespace Ui {
class FileWidget;
}

class FileWidget : public QGroupBox
{
    Q_OBJECT

public:
    explicit FileWidget(QWidget *parent = nullptr);
    ~FileWidget();

    inline QString name() const { return name_; }
    inline QString path() const { return path_; }
    inline FileType type() const { return type_; }
    inline int rowCnt() const { return rowCnt_; }
    inline int colCnt() const { return colCnt_; }
    inline int progress() const { return progress_; }

public slots:
   void setProgress(int progress);
   void setMaxProgress(int maxProgress);
   void setName(const QString &name);
   void setPath(const QString &path);
   void setType(const FileType &type);
   void setRowCnt(int rowCnt);
   void setColCnt(int colCnt);

private:
    Ui::FileWidget *ui;
    QString name_;
    QString path_;
    FileType type_;
    int rowCnt_;
    int colCnt_;
    int progress_;
};

#endif // FILEWIDGET_H
