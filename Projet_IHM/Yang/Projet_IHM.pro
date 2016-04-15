#-------------------------------------------------
#
# Project created by QtCreator 2014-04-23T14:38:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_IHM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp \
    petitwindow.cpp \
    treemodel.cpp \
    treeitem.cpp

HEADERS  += mainwindow.h \
    dialog.h \
    petitwindow.h \
    treemodel.h \
    treeitem.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    notes.qrc
