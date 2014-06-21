#include "QtReadabilityApi.h"

#include "ReadabilityHttpRequest.h"
#include "ReadabilityArticle.h"
#include "ReadabilityConfidence.h"

#include <QtQml>

const QString QtReadabilityParserApi::BaseUrl = "https://readability.com/api/content";

QtReadabilityParserApi::QtReadabilityParserApi(ReadabilityApiVersion version,
                                               QByteArray token,
                                               QObject* parent)
    : QObject(parent),
      m_version(version),
      m_token(token)
{
    qRegisterMetaType<ReadabilityArticle*>();
    qRegisterMetaType<ReadabilityConfidence*>();

    qmlRegisterType<ReadabilityArticle>();
    qmlRegisterType<ReadabilityConfidence>();
}

ReadabilityConfidence* QtReadabilityParserApi::parseConfidence(QUrl url)
{
    Q_UNUSED(url);
    return 0;
}

ReadabilityArticle* QtReadabilityParserApi::parseUrl(QUrl url)
{
    ReadabilityArticle* article = new ReadabilityArticle(this);
    article->setUrl(url);
    return article;
}

QString QtReadabilityParserApi::versionString()
{
    return QString("v%1").arg(m_version.majorVersion);
}

ReadabilityApiVersion QtReadabilityParserApi::version()
{
    return m_version;
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
