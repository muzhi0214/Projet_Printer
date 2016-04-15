#-------------------------------------------------
#
# Project created by QtCreator 2014-05-01T15:09:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_IHM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aspect.cpp \
    fichier.cpp \
    nouveaudialog.cpp \
    petitwindow.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS  += mainwindow.h \
    aspect.h \
    fichier.h \
    nouveaudialog.h \
    petitwindow.h \
    treeitem.h \
    treemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
