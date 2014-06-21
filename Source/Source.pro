#-------------------------------------------------
#
# Project created by QtCreator 2014-06-19T18:49:35
#
#-------------------------------------------------

QT       += qml quick network
QT       -= gui
CONFIG   += qt plugin
TEMPLATE  = lib
TARGET    = $$qtLibraryTarget(QtReadability)

uri = Qtino.Readability

DEFINES += QTREADABILITY_LIBRARY

SOURCES += QtReadabilityApi.cpp \
    ReadabilityArticle.cpp \
    ReadabilityConfidence.cpp \
    ReadabilityHttpRequest.cpp \
    ReadabilityArticleLoader.cpp \
    ReadabilityConfidenceLoader.cpp \
    QtReadabilityPlugin.cpp

HEADERS += QtReadabilityApi.h\
    QtReadability_Global.h \
    ReadabilityArticle.h \
    ReadabilityConfidence.h \
    ReadabilityHttpRequest.h \
    ReadabilityArticleLoader.h \
    ReadabilityConfidenceLoader.h \
    QtReadabilityPlugin.h

OTHER_FILES += \
    qmldir

QMAKE_MOC_OPTIONS += -Muri=$$uri

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)

cleanTarget.files +=
cleanTarget.path += $$installPath
macx: cleanTarget.extra = rm -rf $$installPath
ios: cleanTarget.extra = rm -rf $$installPath

qmldir.files = qmldir
qmldir.path = $$installPath
target.path = $$installPath

INSTALLS += cleanTarget target qmldir
