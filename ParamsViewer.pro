#-------------------------------------------------
#
# Project created by QtCreator 2018-08-29T00:49:35
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ParamsViewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += services

SOURCES += \
        main.cpp \
        mainwindow.cpp \
        model/descriptor.cpp \
        model/obj.cpp \
        model/imageobjectsfile.cpp \
        services/fileservice.cpp \
        services/floatservice.cpp \
        services/itemsservice.cpp \
        services/stringservice.cpp \
        widgets/bulkutilitydialog.cpp \
        widgets/filewidget.cpp \
        widgets/chartwidget.cpp

HEADERS += \
        mainwindow.h \
        model/descriptor.h \
        model/obj.h \
        model/imageobjectsfile.h \
        services/fileservice.h \
        services/floatservice.h \
        services/itemsservice.h \
        services/stringservice.h \
        services.h \
        widgets/bulkutilitydialog.h \
        widgets/filewidget.h \
        widgets/chartwidget.h

FORMS += \
        mainwindow.ui \
        widgets/bulkutilitydialog.ui \
        widgets/filewidget.ui \
        widgets/chartwidget.ui

RESOURCES += \
        sources.qrc

win32: RC_FILE = iconsource.rc
