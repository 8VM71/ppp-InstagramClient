include($$PWD/../VKClient/common.pri)

QT       += core gui

TARGET = PostsCalcModule
TEMPLATE = lib
CONFIG += plugin c++11

DESTDIR = $${APP_MODULEPATH}

INCLUDEPATH += $${APP_INCLUDEPATH}

SOURCES += \
        postscalcplugin.cpp

HEADERS += \
        postscalcplugin.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
