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

PUBLIC_HEADERS += QtReadability_Global.h \
                  QtReadabilityApi.h \
                  ReadabilityArticle.h \
                  ReadabilityConfidence.h \
                  QtReadability

HEADERS += \
    $$PUBLIC_HEADERS \
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
includePath = $$[QT_INSTALL_HEADERS]/$$replace(uri, \\., /)

unix: { libprefix = lib }
win32: { libprefix = }

CONFIG(static, static|shared) {
    macx|ios|unix: { libsuffix = a }
    win32: { libsuffix = lib }
}
else {
    macx: { libsuffix = dylib }
    unix:!macx: { libsuffix = so }
    win32: { libsuffix = lib }
}

cleanTarget.files +=
cleanTarget.path += $$installPath
macx|ios|unix: cleanTarget.extra = rm -rf $$installPath/*.qml $$installPath/qmldir $$installPath/plugins.qmltypes $$installPath/$$libprefix$$TARGET$${qtPlatformTargetSuffix}.$$libsuffix

headers.files = $$PUBLIC_HEADERS
headers.path = $$includePath

universalInclude.files = QtReadability
universalInclude.path = $$includePath/..

qmldir.files = qmldir
qmldir.path = $$installPath
target.path = $$installPath

plugindump.files +=
plugindump.path = $$installPath
macx {
    plugindump.extra = qmlplugindump $$uri 1.0 > $$installPath/plugins.qmltypes
}

INSTALLS += cleanTarget target qmldir plugindump headers universalInclude

QMAKE_POST_LINK += make install
