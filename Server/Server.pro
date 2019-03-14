#-------------------------------------------------
#
# Project created by QtCreator 2019-02-21T19:20:54
#
#-------------------------------------------------

QT       += core gui
QT       += network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

LIBS += -lws2_32

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    myserverfile.cpp \
    clientservice.cpp

HEADERS += \
        mainwindow.h \
    myserverfile.h \
    clientservice.h \
    networkthread.h \
    networkthread.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += $$PWD/../Common/socketreadwrite
DEPENDPATH += $$PWD/../Common/socketreadwrite

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Common/socketreadwrite/release/ -lsocketreadwrite
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Common/socketreadwrite/debug/ -lsocketreadwrite
else:unix: LIBS += -L$$OUT_PWD/../Common/socketreadwrite/ -lsocketreadwrite

INCLUDEPATH += $$PWD/../Common/socketreadwrite
DEPENDPATH += $$PWD/../Common/socketreadwrite

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/socketreadwrite/release/libsocketreadwrite.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/socketreadwrite/debug/libsocketreadwrite.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/socketreadwrite/release/socketreadwrite.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../Common/socketreadwrite/debug/socketreadwrite.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../Common/socketreadwrite/libsocketreadwrite.a
