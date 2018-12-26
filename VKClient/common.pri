CONFIG(debug, debug|release) {
    APP_DESTDIR = $$PWD/../bin/debug
} else {
    APP_DESTDIR = $$PWD/../bin/release
}

APP_INCLUDEPATH = $$PWD/include

APP_MODULEPATH = $${APP_DESTDIR}/modules
