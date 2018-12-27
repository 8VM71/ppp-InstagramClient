include($$PWD/../VKClient/common.pri)

QT       += core gui

TARGET = PhotosCalcModule
TEMPLATE = lib
CONFIG += plugin c++11

DESTDIR = $${APP_MODULEPATH}

INCLUDEPATH += $${APP_INCLUDEPATH}

SOURCES += \
    photoscalcplugin.cpp

HEADERS += \
    photoscalcplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
