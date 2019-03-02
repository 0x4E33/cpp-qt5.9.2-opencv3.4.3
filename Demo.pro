#-------------------------------------------------
#
# Project created by QtCreator 2019-02-28T00:25:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo
TEMPLATE = app

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
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui


INCLUDEPATH += \
        E:\opencv\install\include  \
        E:\opencv\install\include\opencv \
        E:\opencv\install\include\opencv2 \

LIBS += \
        E:\opencv\install\x64\vc15\lib\opencv_world343d.lib \

win32: LIBS += -LE:/Python/Python36/libs/ -lpython36

INCLUDEPATH += E:/Python/Python36/include
DEPENDPATH += E:/Python/Python36/include

win32:!win32-g++: PRE_TARGETDEPS += E:/Python/Python36/libs/python36.lib
else:win32-g++: PRE_TARGETDEPS += E:/Python/Python36/libs/libpython36.a
