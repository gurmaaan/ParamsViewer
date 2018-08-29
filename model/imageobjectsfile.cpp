#include "imageobjectsfile.h"
ImageObjectsFile::ImageObjectsFile(QObject *parent) : QObject(parent)
{

}

void ImageObjectsFile::loadCSV(const QString &filePath)
{
    filePath_ = filePath;
}

void ImageObjectsFile::setModel(QStandardItemModel *model)
{
    model_ = model;
}

void ImageObjectsFile::setDescrNameList(const QStringList &descrNameList)
{
    descrNameList_ = descrNameList;
}

void ImageObjectsFile::setObjNamesList(const QStringList &objNamesList)
{
    objNamesList_ = objNamesList;
}

void ImageObjectsFile::setObOnImVect(const QVector<Obj *> &obOnImVect)
{
    obOnImVect_ = obOnImVect;
}

void ImageObjectsFile::setRowInFileCnt(int rowInFileCnt)
{
    rowInFileCnt_ = rowInFileCnt;
}

void ImageObjectsFile::setColInFileCnt(int colInFileCnt)
{
    colInFileCnt_ = colInFileCnt;
}
