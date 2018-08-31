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
        QVector<QString> firstRowList = StringService::splitAndRemoveFirstColOfFirstRow(fileText).toVector();
        for(QString colName : firstRowList)
        {
            if( StringService::notEmpty(colName) )
            {
                addToDscrNameList(colName);
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

        QVector<QString> fileRowsList = StringService::splitAndRemoveFirstRow(fileText).toVector();
        QVector<Obj*> objInFileVector;
        for(int r = 0; r < rowInFileCnt_; r++)
        {
            QString rowString = fileRowsList.at(r);
            if( StringService::notEmpty(rowString) )
            {
                QString objectFullName = StringService::getFirstCol(rowString);
                addToObjcNameList(objectFullName);

                Obj* objAtR = new Obj(r,  objectFullName);
                QStringList itemsStrListAtR = StringService::splitAndRemoveFirstColOfFirstRow(rowString);
                QList<QStandardItem*> rowAtR;

                for(int c = 0; c < colInFileCnt_; c++)
                {
                    QString itemString = itemsStrListAtR.at(c);
                    QStandardItem* itemAtRC = new QStandardItem();

                    FloatService::replaceCommaToPoint(&itemString);
                    itemAtRC->setData(itemString, Qt::EditRole);

                    double itemAtRCVal = itemString.toDouble();
                    itemAtRC->setData(ItemsService::displayingStr(itemAtRCVal), Qt::DisplayRole);
                    Descriptor *descriptorAtRC = new Descriptor(r, c, descrNameList_.at(c), itemAtRCVal);

                    objAtR->apendDescriptor(descriptorAtRC);
                    rowAtR.append(itemAtRC);
                }
                objInFileVector << objAtR;
                model_->appendRow(rowAtR);
                addHeader(model_, objectFullName, Qt::Vertical);
            }
            emit rowProccessed(r);
        }
        emit modelChenged(model_);
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
    objOnImVect_ = obOnImVect;
}

void ImageObjectsFile::setRowInFileCnt(int rowInFileCnt)
{
    rowInFileCnt_ = rowInFileCnt;
}

void ImageObjectsFile::setColInFileCnt(int colInFileCnt)
{
    colInFileCnt_ = colInFileCnt;
}

void ImageObjectsFile::addToObjcNameList(QString newName)
{
    objNamesList_.append(newName);
}

void ImageObjectsFile::addToDscrNameList(QString newName)
{
    descrNameList_.append(newName);
}

void ImageObjectsFile::addHeader(QStandardItemModel *m, QString headerStr, Qt::Orientation o)
{
    QStandardItem *hItem = new QStandardItem();
    hItem->setData(headerStr, Qt::EditRole);
    ItemsService::makeHeader(hItem, o);
    if(o == Qt::Horizontal)
    {
        hItem->setData( StringService::multipleLineFromSingle(headerStr), Qt::DisplayRole );
        ItemsService::addDescription(hItem, headerStr);
        m->setHorizontalHeaderItem(m->columnCount(), hItem);
    }
    else
    {
        ItemsService::addDescription(hItem, headerStr);
        hItem->setData( FileService::fileName(headerStr), Qt::DisplayRole);
        m->setVerticalHeaderItem( m->rowCount() - 1, hItem );
    }
}
