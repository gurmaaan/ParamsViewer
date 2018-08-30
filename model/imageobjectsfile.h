#ifndef IMAGEOBJECTSFILE_H
#define IMAGEOBJECTSFILE_H

#include <QObject>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QStringList>

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
    inline QStringList          descrNameList() const { return descrNameList_;  }
    inline int                  colInFileCnt()  const { return colInFileCnt_;   }
    inline QStringList          objNamesList()  const { return objNamesList_;   }
    inline int                  rowInFileCnt()  const { return rowInFileCnt_;   }
    inline QVector<Obj *>       obOnImVect()    const { return obOnImVect_;     }

public slots:
    void setFilePath(const QString &filePath);
    void loadCSVText(const QString &fileText);
    void setModel(QStandardItemModel *model);
    void setDescrNameList(const QStringList &descrNameList);
    void setObjNamesList(const QStringList &objNamesList);
    void setObOnImVect(const QVector<Obj *> &obOnImVect);
    void setRowInFileCnt(int rowInFileCnt);
    void setColInFileCnt(int colInFileCnt);

signals:
    void modelChenged(QStandardItemModel* newModel);
    void fileColCntChanged(int newColCnt);
    void fileRowCntChanged(int newRowCnt);
    void firstCOlOfFirstrRowChanged(QString frofcStr);

private:
    QString filePath_;
    int colInFileCnt_;
    int rowInFileCnt_;

    QVector<Obj *> obOnImVect_;
    QStringList objNamesList_;
    QStringList descrNameList_;
    QStandardItemModel *model_;

    QVector<Obj *> parseObjVector(QString fileText) const;
};

#endif // IMAGEOBJECTSFILE_H
