include(common.pri)

QT += quick
CONFIG += c++11

DESTDIR = $${APP_DESTDIR}

INCLUDEPATH += \
    $${APP_INCLUDEPATH} \
    $$PWD/src

HEADERS += \
    $$files($$PWD/include/*.h) \
    $$files($$PWD/src/*.h, true)

SOURCES += \
    $$files($$PWD/src/*.cpp, true)

RESOURCES += $$PWD/ui/qml.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

