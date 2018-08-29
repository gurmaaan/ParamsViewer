#ifndef IMAGEOBJECTSFILE_H
#define IMAGEOBJECTSFILE_H

#include <QObject>
#include <QStandardItemModel>
#include "model/obj.h"
#include "model/descriptor.h"

class ImageObjectsFile : public QObject
{
    Q_OBJECT
public:
    explicit ImageObjectsFile(QObject *parent = nullptr);
    ImageObjectsFile(QString path, QObject *parent = nullptr);

    inline QString filePath() const { return filePath_; }
    inline QStandardItemModel *model() const { return model_; }
    inline QStringList descrNameList() const;
    inline int colInFileCnt() const { return colInFileCnt_; }
    inline QStringList objNamesList() const { return objNamesList_; }
    inline int rowInFileCnt() const { return rowInFileCnt_; }
    inline QVector<Obj *> obOnImVect() const { return obOnImVect_; }

public slots:
    void loadCSV(const QString &filePath);
    void setModel(QStandardItemModel *model);
    void setDescrNameList(const QStringList &descrNameList);
    void setObjNamesList(const QStringList &objNamesList);
    void setObOnImVect(const QVector<Obj *> &obOnImVect);
    void setRowInFileCnt(int rowInFileCnt);
    void setColInFileCnt(int colInFileCnt);

signals:
    void modelChenged(QStandardItemModel* newModel);

private:
    QString filePath_;
    int colInFileCnt_;
    int rowInFileCnt_;

    QVector<Obj *> obOnImVect_;
    QStringList objNamesList_;
    QStringList descrNameList_;

    QStandardItemModel *model_;
};

#endif // IMAGEOBJECTSFILE_H
