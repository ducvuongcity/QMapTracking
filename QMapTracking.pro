QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMapTracking
TEMPLATE = app

SOURCES += main.cpp \
    src/ccDialog.cpp \
    src/ccReaderManager.cpp

HEADERS += \
    hdr/ccDialog.h \
    hdr/ccReaderManager.h \
    hdr/common.h
