QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMapTracking
TEMPLATE = app

SOURCES += main.cpp \
    ccDialog.cpp \
    ccReaderManager.cpp

HEADERS += \
    ccDialog.h \
    ccReaderManager.h \
    common.h
