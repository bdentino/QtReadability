#ifndef READABILITYCONFIDENCE_H
#define READABILITYCONFIDENCE_H

#include <QObject>
#include <QJsonObject>
#include <QUrl>
#include <QtNetwork>

#include "QtReadability_Global.h"

class QtReadabilityParserApi;
class ReadabilityHttpRequest;
class QTREADABILITYSHARED_EXPORT ReadabilityConfidence : public QObject
{
    Q_OBJECT

    Q_PROPERTY(double confidence READ confidence NOTIFY loadingChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY loadingChanged)

    Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)

    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    explicit ReadabilityConfidence(QObject* parent = 0);

    double confidence();
    QUrl url();

    bool isLoading();

    QString error();

    void setUrl(QUrl url);
    void setApi(QtReadabilityParserApi* api);

signals:
    void loadingChanged();
    void errorChanged(QString description);

public slots:
    virtual void fromJsonObject(QJsonObject description);

protected slots:
    void tryLoad();

private slots:
    void onResponseReceived(QJsonObject response);
    void onRequestError(QNetworkReply::NetworkError error, QString description);

private:
    double m_confidence;
    QUrl m_url;

    QString m_error;

    QtReadabilityParserApi* m_api;
    ReadabilityHttpRequest* m_request;
};

#endif // READABILITYCONFIDENCE_H
