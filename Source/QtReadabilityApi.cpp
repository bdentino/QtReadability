#include "QtReadabilityApi.h"

#include "ReadabilityHttpRequest.h"
#include "ReadabilityArticle.h"
#include "ReadabilityConfidence.h"
#include "ReadabilityArticleLoader.h"
#include "ReadabilityConfidenceLoader.h"

#include <QtQml>

const QString QtReadabilityParserApi::BaseUrl = "https://readability.com/api/content";

QtReadabilityParserApi::QtReadabilityParserApi(QObject* parent)
    : QObject(parent)
{
    qRegisterMetaType<ReadabilityArticle*>();
    qRegisterMetaType<ReadabilityConfidence*>();
    qRegisterMetaType<QtReadabilityParserApi*>();

    qmlRegisterType<ReadabilityArticle>();
    qmlRegisterType<ReadabilityConfidence>();
    qmlRegisterType<QtReadabilityParserApi>();
}

QtReadabilityParserApi::QtReadabilityParserApi(ReadabilityApiVersion version, QByteArray token,
                                               QObject* parent)
    : QObject(parent),
      m_version(version),
      m_token(token)
{
    qRegisterMetaType<ReadabilityArticle*>();
    qRegisterMetaType<ReadabilityConfidence*>();
    qRegisterMetaType<QtReadabilityParserApi*>();

    qmlRegisterType<ReadabilityArticle>();
    qmlRegisterType<ReadabilityConfidence>();
    qmlRegisterType<QtReadabilityParserApi>();
}

ReadabilityConfidence* QtReadabilityParserApi::parseConfidence(QUrl url)
{
    ReadabilityConfidence* confidence = new ReadabilityConfidence(this);
    confidence->setUrl(url);
    return confidence;
}

ReadabilityArticle* QtReadabilityParserApi::parseUrl(QUrl url)
{
    ReadabilityArticle* article = new ReadabilityArticle(this);
    article->setUrl(url);
    return article;
}

void QtReadabilityParserApi::setVersion(QString version)
{
    ReadabilityApiVersion defaultVersion;
    if (m_version != defaultVersion) {
        qWarning("Cannot change API version after initialization.");
        return;
    }
    m_version = ReadabilityApiVersion(version);
}

QString QtReadabilityParserApi::versionString() const
{
    return m_version.toString();
}

ReadabilityApiVersion QtReadabilityParserApi::version() const
{
    return m_version;
}

void QtReadabilityParserApi::setToken(const QByteArray token)
{
    if (m_token != QByteArray()) {
        qWarning("Cannot change API token after initialization.");
        return;
    }
    m_token = token;
}

const QByteArray QtReadabilityParserApi::token() const
{
    return m_token;
}

ReadabilityHttpRequest* QtReadabilityParserApi::getParseRequest(QUrl articleUrl)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("url", articleUrl.toString());
    urlQuery.addQueryItem("token", m_token);
    QString path = QString("/%1/parser").arg(versionString());
    QUrl url(QtReadabilityParserApi::BaseUrl + path);
    url.setQuery(urlQuery);
    return new ReadabilityHttpRequest(url);
}

ReadabilityHttpRequest* QtReadabilityParserApi::getConfidenceRequest(QUrl articleUrl)
{
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("url", articleUrl.toString());
    urlQuery.addQueryItem("token", m_token);
    QString path = QString("/%1/confidence").arg(versionString());
    QUrl url(QtReadabilityParserApi::BaseUrl + path);
    url.setQuery(urlQuery);
    return new ReadabilityHttpRequest(url);
}

QJsonObject QtReadabilityParserApi::parseArticleResponse(QJsonObject response)
{
    return response;
}

QJsonObject QtReadabilityParserApi::parseConfidenceResponse(QJsonObject response)
{
    return response;
}
