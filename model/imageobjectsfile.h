#ifndef IMAGEOBJECTSFILE_H
#define IMAGEOBJECTSFILE_H

#include <QObject>
#include <QStandardItemModel>
#include <QMessageBox>

#include "model/obj.h"
#include "model/descriptor.h"
#include "services.h"

class ImageObjectsFile : public QObject
{
    Q_OBJECT
public:
    explicit ImageObjectsFile(QObject *parent = nullptr);
    ImageObjectsFile(QString path, QObject *parent = nullptr);

    inline QString              filePath()      const { return filePath_;       }
    inline QStandardItemModel   *model()        const { return model_;          }
    inline QVector<QString>     descrNameList() const { return descrNameList_;  }
    inline int                  colInFileCnt()  const { return colInFileCnt_;   }
    inline QVector<QString>     objNamesList()  const { return objNamesList_;   }
    inline int                  rowInFileCnt()  const { return rowInFileCnt_;   }
    inline QVector<Obj *>       obOnImVect()    const { return objOnInVect_;    }



public slots:
    void setFilePath(const QString &filePath);
    void loadCSVText(const QString &fileText);
    void setModel(QStandardItemModel *model);
    void setDescrNameList(const QVector<QString> &descrNameList);
    void setObjNamesList(const QVector<QString> &objNamesList);
    void setObOnImVect(const QVector<Obj *> &obOnImVect);
    void setRowInFileCnt(int rowInFileCnt);
    void setColInFileCnt(int colInFileCnt);

signals:
    void modelChenged(QStandardItemModel* newModel);
    void firstCOlOfFirstrRowChanged(QString frofcStr);
    void rowProccessed(int curRow);

private:
    QString filePath_;
    int colInFileCnt_;
    int rowInFileCnt_;

    QVector<QString> descrNameList_;
    QVector<Obj *> objOnInVect_;
    QVector<QString> objNamesList_;
    QStandardItemModel *model_;

    QVector<Obj *> parseObjVector(QString fileText);
    void addToDescrNameList(QString newName);
    void addHeader(QStandardItemModel *m, QString headerStr, Qt::Orientation o);
};

#endif // IMAGEOBJECTSFILE_H
