QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


DESTDIR = $$PWD/../bin

include($$PWD/cell/cell.pri)
include($$PWD/lib/lib.pri)

RESOURCES += \
    res/res.qrc


RC_FILE = $$PWD/res/app.rc
