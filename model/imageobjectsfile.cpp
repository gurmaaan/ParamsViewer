#include "imageobjectsfile.h"

ImageObjectsFile::ImageObjectsFile(QObject *parent) : QObject(parent)
{
    filePath_ = " ";
}

void ImageObjectsFile::loadCSVText(const QString &fileText)
{
    if(fileText != "")
    {
        obOnImVect_ = parseObjVector(fileText);
    }
}

void ImageObjectsFile::setFilePath(const QString &filePath)
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

QVector<Obj *> ImageObjectsFile::parseObjVector(QString fileText) const
{
    for(auto hHItemText : StringService::splitAndRemoveFirstColOfFirstRow(fileText) )
    {
        if( StringService::notEmpty(hHItemText) )
            descrNameList_ << hHItemText;
        else
        {
            int ret = QMessageBox::information(this, Msg::header(MessageType::Warrning),
                                                     Msg::body(ErrorType::EmptyCell),
                                                     QMessageBox::Ok | QMessageBox::Cancel);
            if(ret == static_cast<int>(QMessageBox::Ok))
                break;
            else
            {
                qDebug() << ret;
                //TODO::Действие закрытия файла
            }
        }
    }
    int descrCnt = descrNameList_.count();
    emit colCountinModelChanged(descrCnt);

    QStringList rowsList = StringService::splitAndRemoveFirstRow(wholeFileText);
    int rowsInFCnt = rowsList.count();
    emit rowCountInFileChanged(rowsInFCnt);

    QVector<Obj*> objInFileVector;
    for(int r = 0; r < rowsInFCnt; r++)
    {
        QString rowString = rowsList.at(r);
        if( StringService::notEmpty(rowString) )
        {

            QString objectName = StringService::getFirstCol(rowString);
            objNameList_ << objectName;
            Obj* objAtRowR = new Obj( r,  objectName);
            QStringList itemsOfRowStringList = StringService::splitAndRemoveFirstColOfFirstRow(rowString);
            for(int c = 0; c < descrCnt; c++)
            {
                QString itemString = itemsOfRowStringList.at(c);
                StringService::replaceForDouble(itemString);
                Descriptor *descriptorAtRC = new Descriptor(r, c, descrNameList_.at(c), itemString.toDouble());
                objAtRowR->apendDescriptor(descriptorAtRC);
            }
            objInFileVector << objAtRowR;
        }
        emit objectProccessed(r);
    }
    return objInFileVector;
}
