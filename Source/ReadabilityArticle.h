#ifndef READABILITYARTICLE_H
#define READABILITYARTICLE_H

#include <QObject>
#include <QJsonObject>
#include <QUrl>
#include <QDateTime>
#include <QtNetwork>

#include "QtReadability_Global.h"

class QtReadabilityParserApi;
class ReadabilityHttpRequest;
class QTREADABILITYSHARED_EXPORT ReadabilityArticle : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY loadingChanged)
    Q_PROPERTY(QtReadabilityParserApi* api READ api WRITE setApi)

    Q_PROPERTY(QString htmlContent READ htmlContent NOTIFY loadingChanged)
    Q_PROPERTY(QUrl domain READ domain NOTIFY loadingChanged)
    Q_PROPERTY(QString author READ author NOTIFY loadingChanged)
    Q_PROPERTY(QUrl shortUrl READ shortUrl NOTIFY loadingChanged)
    Q_PROPERTY(QString title READ title NOTIFY loadingChanged)
    Q_PROPERTY(QString htmlExcerpt READ htmlExcerpt NOTIFY loadingChanged)
    Q_PROPERTY(Qt::LayoutDirection direction READ direction NOTIFY loadingChanged)
    Q_PROPERTY(int wordCount READ wordCount NOTIFY loadingChanged)
    Q_PROPERTY(int totalPages READ totalPages NOTIFY loadingChanged)
    Q_PROPERTY(QDateTime publishedDate READ publishedDate NOTIFY loadingChanged)
    Q_PROPERTY(QString htmlDek READ htmlDek NOTIFY loadingChanged)
    Q_PROPERTY(QUrl leadImageSource READ leadImageSource NOTIFY loadingChanged)
    Q_PROPERTY(QString nextPageId READ nextPageId NOTIFY loadingChanged)
    Q_PROPERTY(int parsedPages READ parsedPages NOTIFY loadingChanged)

    Q_PROPERTY(bool isLoading READ isLoading NOTIFY loadingChanged)

    Q_PROPERTY(QString error READ error NOTIFY errorChanged)

public:
    explicit ReadabilityArticle(QObject* parent = 0);

    QtReadabilityParserApi* api();
    QString htmlContent();
    QUrl domain();
    QString author();
    QUrl url();
    QUrl shortUrl();
    QString title();
    QString htmlExcerpt();
    Qt::LayoutDirection direction();
    int wordCount();
    int totalPages();
    QDateTime publishedDate();
    QString htmlDek();
    QUrl leadImageSource();
    QString nextPageId();
    int parsedPages();

    bool isLoading();

    QString error();

    void setUrl(QUrl url);
    void setApi(QtReadabilityParserApi* m_api);

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
    QString m_htmlContent;
    QUrl m_domain;
    QString m_author;
    QUrl m_url;
    QUrl m_shortUrl;
    QString m_title;
    QString m_htmlExcerpt;
    Qt::LayoutDirection m_direction;
    int m_wordCount;
    int m_totalPages;
    QDateTime m_publishedDate;
    QString m_htmlDek;
    QUrl m_leadImageSource;
    QString m_nextPageId;
    int m_parsedPages;

    QString m_error;

    QtReadabilityParserApi* m_api;
    ReadabilityHttpRequest* m_request;
};

#endif // READABILITYARTICLE_H
