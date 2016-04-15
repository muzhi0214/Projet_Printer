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
    petitwindow.cpp \
    fichier.cpp \
    aspect.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS  += mainwindow.h \
    petitwindow.h \
    fichier.h \
    aspect.h \
    treeitem.h \
    treeitem.h \
    treemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    icon.qrc
