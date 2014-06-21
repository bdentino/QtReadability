TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += qml.qrc

INCLUDEPATH += $$PWD/../../Source

LIBS += -L../../Source -lQtReadability

macx {
    PRE_TARGETDEPS += ../../Source/libQtReadability.dylib

    sharedLibs.path = Contents/MacOS
    sharedLibs.files += $$OUT_PWD/../../Source/libQtReadability.1.dylib

    for(lib, sharedLibs.files) {
        QMAKE_POST_LINK += "cp $${lib} $${TARGET}.app/$${sharedLibs.path}/;"
    }
}
