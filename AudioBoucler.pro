#-------------------------------------------------
#
# Project created by QtCreator 2015-05-01T15:22:17
#
#-------------------------------------------------

QT       += core gui multimedia

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioBoucler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    zonedessin.cpp \
    lecteur.cpp \
    infopiste.cpp \
    playlist.cpp \
    conversion.cpp

HEADERS  += mainwindow.h \
    zonedessin.h \
    lecteur.h \
    infopiste.h \
    playlist.h \
    conversion.h

FORMS    += mainwindow.ui \

RESOURCES += \
    application.qrc
