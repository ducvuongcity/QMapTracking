QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMapTracking
TEMPLATE = app

SOURCES += main.cpp \
    src/ccDialog.cpp \
    src/ccDataManager.cpp \
    src/ccController.cpp \
    src/widget/QMapContainer.cpp \
    src/ccBridge.cpp \
    src/ccDataStore.cpp

HEADERS += \
    hdr/common.h \
    hdr/ccDialog.h \
    hdr/ccDataManager.h \
    hdr/ccController.h \
    hdr/widget/QMapContainer.h \
    hdr/ccBridge.h \
    hdr/ccDataStore.h

INCLUDEPATH += hdr \
    hdr/widget \
    src \
    src/widget

