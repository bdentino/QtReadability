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
    unsigned short minorVersion;

    ReadabilityApiVersion(QString version)
    {
        if (version.startsWith("v")) version = version.mid(1);
        QStringList parts = version.split(".");
        if (parts.length() < 1) return;
        majorVersion = parts.at(0).toShort();
        if (parts.length() < 2) return;
        minorVersion = parts.at(1).toShort();
    }
};

class ReadabilityArticle;
class ReadabilityConfidence;
class ReadabilityHttpRequest;
class QTREADABILITYSHARED_EXPORT QtReadabilityParserApi : public QObject
{
    friend class ReadabilityArticle;
    friend class ReadabilityConfidence;
    Q_OBJECT

public:
    QtReadabilityParserApi(ReadabilityApiVersion version, QByteArray token,
                           QObject* parent = 0);

    ReadabilityConfidence* parseConfidence(QUrl url);

    //TODO: This allows you to immediately get a reference to an object that updates
    //      as data comes in. It may be useful to have a secondary method of requesting
    //      a url that returns the 'ready' object via a signal after all loading is done.
    ReadabilityArticle* parseUrl(QUrl url);

    QString versionString();
    ReadabilityApiVersion version();

protected:
    ReadabilityHttpRequest* getParseRequest(QUrl articleUrl);

private:
    ReadabilityApiVersion m_version;
    const QByteArray m_token;

    static const QString BaseUrl;
};

#endif // QTREADABILITYAPI_H
