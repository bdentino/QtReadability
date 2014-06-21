#ifndef QTREADABILITYPLUGIN_H
#define QTREADABILITYPLUGIN_H

#include <QQmlExtensionPlugin>

class QtReadabilityPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char* uri);
};

#endif // QTREADABILITYPLUGIN_H
