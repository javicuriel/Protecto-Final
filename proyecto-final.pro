#-------------------------------------------------
#
# Project created by QtCreator 2015-11-16T22:03:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyecto-final
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    lectorarchivos.cpp

HEADERS  += mainwindow.h \
    nodoB.h \
    BinarySTree.h \
    BinaryTree.h \
    avl.h \
    edge.h \
    rojinegro.h \
    arboldostres.h \
    nododostres.h \
    lectorarchivos.h

FORMS    += mainwindow.ui
CONFIG += c++11


