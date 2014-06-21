#ifndef QTREADABILITYAPI_H
#define QTREADABILITYAPI_H

#include "QtReadability_Global.h"

#include <QObject>
#include <QStringList>
#include <QUrl>

//TODO: Using a lot of the same patterns here as with QtGoogleFeeds Api wrapper
//      Consider making a base project for things like version structs, http requesters, etc
//      that apply to any RESTful interface

struct QTREADABILITYSHARED_EXPORT ReadabilityApiVersion {
    unsigned short majorVersion;
    unsigned short minorVersion; //Currently not used, but keeping for extensibility

    ReadabilityApiVersion(QString version)
    {
        if (version.startsWith("v")) version = version.mid(1);
        QStringList parts = version.split(".");
        if (parts.length() < 1) return;
        majorVersion = parts.at(0).toShort();
        if (parts.length() < 2) return;
        minorVersion = parts.at(1).toShort();
    }

    ReadabilityApiVersion()
    {
        majorVersion = 0;
        minorVersion = 0;
    }

    QString toString() const
    {
        return QString("v%1").arg(majorVersion);
    }

    bool operator==(const ReadabilityApiVersion& rhs)
    {
        return majorVersion == rhs.majorVersion && minorVersion == rhs.minorVersion;
    }

    bool operator!=(const ReadabilityApiVersion& rhs)
    {
        return !(*this == rhs);
    }
};

class ReadabilityArticle;
class ReadabilityConfidence;
class ReadabilityHttpRequest;
class ReadabilityArticleLoader;
class ReadabilityConfidenceLoader;
class QTREADABILITYSHARED_EXPORT QtReadabilityParserApi : public QObject
{
    friend class ReadabilityArticle;
    friend class ReadabilityConfidence;
    Q_OBJECT

    Q_PROPERTY(QByteArray token READ token WRITE setToken)
    Q_PROPERTY(QString version READ versionString WRITE setVersion)

public:
    QtReadabilityParserApi(QObject* parent = 0);

    QtReadabilityParserApi(ReadabilityApiVersion version, QByteArray token,
                           QObject* parent = 0);

    ReadabilityArticle* parseUrl(QUrl url);
    ReadabilityConfidence* parseConfidence(QUrl url);

    ReadabilityArticleLoader* getArticleLoader(QUrl url);
    ReadabilityConfidenceLoader* getConfidenceLoader(QUrl url);

    void setVersion(QString version);
    QString versionString() const;
    ReadabilityApiVersion version() const;

    void setToken(const QByteArray token);
    const QByteArray token() const;

protected:
    ReadabilityHttpRequest* getParseRequest(QUrl articleUrl);
    ReadabilityHttpRequest* getConfidenceRequest(QUrl articleUrl);

    QJsonObject parseArticleResponse(QJsonObject response);
    QJsonObject parseConfidenceResponse(QJsonObject response);

private:
    ReadabilityApiVersion m_version;
    QByteArray m_token;

    static const QString BaseUrl;
};

#endif // QTREADABILITYAPI_H
