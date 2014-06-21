#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T18:49:35
#
#-------------------------------------------------

QT       += qml network

QT       -= gui

TARGET = QtReadability
TEMPLATE = lib

DEFINES += QTREADABILITY_LIBRARY

SOURCES += QtReadabilityApi.cpp \
    ReadabilityArticle.cpp \
    ReadabilityConfidence.cpp \
    ReadabilityHttpRequest.cpp

HEADERS += QtReadabilityApi.h\
    QtReadability_Global.h \
    ReadabilityArticle.h \
    ReadabilityConfidence.h \
    ReadabilityHttpRequest.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
