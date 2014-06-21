#ifndef READABILITYCONFIDENCELOADER_H
#define READABILITYCONFIDENCELOADER_H

#include <QObject>
#include <QUrl>

#include "QtReadability_Global.h"

class QtReadabilityParserApi;
class ReadabilityConfidence;
class QTREADABILITYSHARED_EXPORT ReadabilityConfidenceLoader : public QObject
{
    friend class QtReadabilityParserApi;

    Q_OBJECT

    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)

public:
    bool loading();

protected:
    explicit ReadabilityConfidenceLoader(QUrl url, QtReadabilityParserApi* api);

signals:
    void confidenceReady(ReadabilityConfidence* confidence);
    void loadingChanged();

public slots:
    void load();
    void onLoadingChanged();

private:
    ReadabilityConfidence* m_confidence;
    QUrl m_url;
};

#endif // READABILITYCONFIDENCELOADER_H
