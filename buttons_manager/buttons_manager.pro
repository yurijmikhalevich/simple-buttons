#-------------------------------------------------
#
# Project created by QtCreator 2013-04-15T22:32:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simple_buttons
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../serialport/release/ -lQtSerialPort
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../serialport/debug/ -lQtSerialPort
else:unix: LIBS += -L$$OUT_PWD/../serialport/ -lQtSerialPort

INCLUDEPATH += $$PWD/../serialport
DEPENDPATH += $$PWD/../serialport
