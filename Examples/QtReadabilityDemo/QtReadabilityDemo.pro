TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/../../Source

LIBS += -L../../Source -l$$qtLibraryTarget(QtReadability)

macx {
    PRE_TARGETDEPS += ../../Source/lib$$qtLibraryTarget(QtReadability).dylib

    sharedLibs.path = Contents/MacOS
    sharedLibs.files += $$OUT_PWD/../../Source/lib$$qtLibraryTarget(QtReadability).dylib

    for(lib, sharedLibs.files) {
        QMAKE_POST_LINK += "cp $${lib} $${TARGET}.app/$${sharedLibs.path}/;"
    }
}

HEADERS += \
    ApiToken.h
