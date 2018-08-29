#include "fileservice.h"

FileService::FileService(QObject *parent) : QObject(parent)
{

}

QString FileService::initDialogAndGetOpenedFileName(QString title, FileType fType)
{
    QString fileName = QFileDialog::getOpenFileName(nullptr,
                                                    title,
                                                    requiredPath(QDir::current(), DATA_PATH),
                                                    FileService::fileTypeStr(fType) );
    return fileName;

}

QString FileService::requiredPath(QDir currentDir, const QString &redirect, QString defaultLocation)
{

#ifdef Q_OS_MAC
    currentDir.cdUp();
    currentDir.cdUp();
    currentDir.cdUp();
#endif

    currentDir.cdUp();
    currentDir.cd(redirect);
    QString path = (currentDir.exists()) ?  currentDir.absolutePath() : defaultLocation;

    if(currentDir.exists())
    {
        return path;
    } else
    {
       qDebug() << tr("Directory ") << currentDir.absolutePath() << " + " <<  redirect << tr("doesn't exist");
       return "";
    }
}

QString FileService::getTextOfFile(QString path)
{
    QFile file(path);
    QString textOfFile;
    if ( !file.open(QFile::ReadOnly | QFile::Text ) )
    {
        qDebug() << tr(DOESNT_EXIST);
        textOfFile = "";
    } else
    {
         QTextStream in(&file);
         in.setCodec(QTextCodec::codecForName(ENCODING));
         textOfFile = in.readAll();
    }
    file.close();
    return textOfFile;
}

QString FileService::fileTypeStr(FileType fType)
{
    QString fileTypeStr = "*";
    switch (fType) {
    case FileType::Image:
        fileTypeStr = "Image PNG(*.png);;Изображение JPG(*.jpg);;Изображение BMP(*.bmp);;";
        break;
    case FileType::CSV:
        fileTypeStr = "Comma Separatred table *.CSV";
        break;
    case FileType::Excel:
        fileTypeStr = "Excel spreadsheet(*.xls*)";
        break;
    case FileType::Dir:
        fileTypeStr = "Папка";
        break;
    }
    return fileTypeStr;
}

QString FileService::fileExtension(QString path)
{
    QString fileExtension = path.split(".").last();
    return fileExtension;
}

QString FileService::fileName(QString path)
{
    QStringList partsList = path.split("\\");
    return partsList.last();
}


Msg::Msg() {}

QString Msg::getActionString(UsersAction act)
{
    QString actionStr = " ";
    switch (act)
    {
        case UsersAction::Save:
            actionStr = "save";
            break;
        case UsersAction::Open:
            actionStr = "open";
            break;
        case UsersAction::Close:
            actionStr = "close";
            break;
        case UsersAction::Cancel:
            actionStr = "Cancel";
            break;
        case UsersAction::Ok:
            actionStr = "Ok";
            break;
    }
    return actionStr;
}

QString Msg::header(MessageType type)
{
    QString messageHeaderStr = " ";
    switch (type)
    {
        case MessageType::Info:
            messageHeaderStr = "Status";
            break;
        case MessageType::Warrning:
            messageHeaderStr = "Warning";
            break;
        case MessageType::Error:
            messageHeaderStr = "Error";
            break;
        case MessageType::SelectFile:
            messageHeaderStr = "Please select the file";
            break;
        case MessageType::SelectDir:
            messageHeaderStr = "Please select the directory";
            break;
    }
    return messageHeaderStr;
}

