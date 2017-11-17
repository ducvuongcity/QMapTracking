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
    src/ccDataBuilerImage2DInfo.cpp

HEADERS += \
    hdr/ccDialog.h \
    hdr/ccDataManager.h \
    hdr/ccController.h \
    hdr/common.h \
    hdr/widget/QMapContainer.h \
    hdr/ccDataBuilerImage2DInfo.h

INCLUDEPATH += hdr \
    hdr/widget \
    src \
    src/widget

