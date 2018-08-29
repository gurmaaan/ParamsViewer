#ifndef FILESERVICE_H
#define FILESERVICE_H

#include <QObject>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <QFileInfo>

#include "static.h"

enum class FileType
{
    Image,
    CSV,
    Excel,
    Dir
};

class FileService : public QObject
{
    Q_OBJECT
public:
    explicit FileService(QObject *parent = nullptr);
    static QString initDialogAndGetOpenedFileName(QString title, FileType fType);
    static QString getTextOfFile(QString path);

    static QString fileTypeStr(FileType fType);
    static QString fileExtension(QString path);
    static QString fileName(QString path);
private:
    static QString requiredPath(QDir currentDir, const QString &redirect, QString defaultLocation = QString(QStandardPaths::PicturesLocation));
};

enum class UsersAction
{
    Save,
    Open,
    Close,
    Cancel,
    Ok
};

enum class MessageType
{
    Info,
    Warrning,
    Error,
    SelectFile,
    SelectDir
};

class Msg
{
public:
    Msg();
    static QString header(MessageType type);

private:
    static QString getActionString(UsersAction act);
};

#endif // FILESERVICE_H
