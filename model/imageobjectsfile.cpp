#include "imageobjectsfile.h"

ImageObjectsFile::ImageObjectsFile(QObject *parent) : QObject(parent)
{
    filePath_ = " ";
    model_ = new QStandardItemModel();
}

void ImageObjectsFile::loadCSVText(const QString &fileText)
{
    if(fileText != "")
    {
        objOnInVect_ = parseObjVector(fileText);
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

void ImageObjectsFile::setDescrNameList(const QVector<QString> &descrNameList)
{
    descrNameList_ = descrNameList;
}

void ImageObjectsFile::setObjNamesList(const QVector<QString> &objNamesList)
{
    objNamesList_ = objNamesList;
}

void ImageObjectsFile::setObOnImVect(const QVector<Obj *> &obOnImVect)
{
    objOnInVect_ = obOnImVect;
}

void ImageObjectsFile::setRowInFileCnt(int rowInFileCnt)
{
    rowInFileCnt_ = rowInFileCnt;
}

void ImageObjectsFile::setColInFileCnt(int colInFileCnt)
{
    colInFileCnt_ = colInFileCnt;
}

QVector<Obj *> ImageObjectsFile::parseObjVector(QString fileText)
{
    QVector<QString> firstRowList = StringService::splitAndRemoveFirstColOfFirstRow(fileText).toVector();
    for(QString colName : firstRowList)
    {
        if( StringService::notEmpty(colName) )
        {
            addToDescrNameList(colName);
            addHeader(model_, colName, Qt::Horizontal);
        }
        else
        {
            int ret = QMessageBox::information(nullptr, Msg::header(MessageType::Warrning),
                                                     Msg::body(ErrorType::EmptyCell),
                                                     QMessageBox::Ok | QMessageBox::Cancel);
            //Bug::не уверен за точность оператора континью в данном случае
            if(ret == static_cast<int>(QMessageBox::Ok))
                continue;
            else
            {
                qDebug() << ret;
                //TODO::Действие закрытия файла
            }
        }
    }

//    int descrCnt = descrNameList_.count();
//    emit colCountinModelChanged(descrCnt);

//    QStringList rowsList = StringService::splitAndRemoveFirstRow(wholeFileText);
//    int rowsInFCnt = rowsList.count();
//    emit rowCountInFileChanged(rowsInFCnt);

//    QVector<Obj*> objInFileVector;
//    for(int r = 0; r < rowsInFCnt; r++)
//    {
//        QString rowString = rowsList.at(r);
//        if( StringService::notEmpty(rowString) )
//        {

//            QString objectName = StringService::getFirstCol(rowString);
//            objNameList_ << objectName;
//            Obj* objAtRowR = new Obj( r,  objectName);
//            QStringList itemsOfRowStringList = StringService::splitAndRemoveFirstColOfFirstRow(rowString);
//            for(int c = 0; c < descrCnt; c++)
//            {
//                QString itemString = itemsOfRowStringList.at(c);
//                StringService::replaceForDouble(itemString);
//                Descriptor *descriptorAtRC = new Descriptor(r, c, descrNameList_.at(c), itemString.toDouble());
//                objAtRowR->apendDescriptor(descriptorAtRC);
//            }
//            objInFileVector << objAtRowR;
//        }
//        emit objectProccessed(r);
//    }
    emit modelChenged(model_);
    return objOnInVect_;
}

void ImageObjectsFile::addToDescrNameList(QString newName)
{
    descrNameList_.append(newName);
}

void ImageObjectsFile::addHeader(QStandardItemModel *m, QString headerStr, Qt::Orientation o)
{
    QStandardItem *hItem = new QStandardItem();
    hItem->setData(headerStr, Qt::EditRole);
    ItemsService::addDescription(hItem, headerStr);
    ItemsService::makeHeader(hItem, o);
    if(o == Qt::Horizontal)
    {
        hItem->setData( StringService::multipleLineFromSingle(headerStr), Qt::DisplayRole );
        m->setHorizontalHeaderItem(m->columnCount(), hItem);
    }
    else
    {
        hItem->setData( headerStr, Qt::DisplayRole);
        m->setVerticalHeaderItem( m->rowCount(), hItem );
    }
}
