QT += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QMapTracking
TEMPLATE = app

SOURCES += main.cpp \
    src/ccMapWidget.cpp \
    src/ccDataManager.cpp \
    src/ccController.cpp \
    src/widget/ccQLabel.cpp \
    src/ccDataBuilerImage2DInfo.cpp \
    src/ccDialog.cpp \
    ccThreadShowImage.cpp

HEADERS += \
    hdr/ccMapWidget.h \
    hdr/ccDataManager.h \
    hdr/ccController.h \
    hdr/common.h \
    hdr/widget/ccQLabel.h \
    hdr/ccDataBuilerImage2DInfo.h \
    hdr/ccDialog.h \
    ccThreadShowImage.h

INCLUDEPATH += hdr \
    hdr/widget \
    src \
    src/widget

