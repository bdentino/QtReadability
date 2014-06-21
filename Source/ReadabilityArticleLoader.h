#ifndef READABILITYARTICLELOADER_H
#define READABILITYARTICLELOADER_H

#include <QObject>
#include <QUrl>

#include "QtReadability_Global.h"

class QtReadabilityParserApi;
class ReadabilityArticle;
class QTREADABILITYSHARED_EXPORT ReadabilityArticleLoader : public QObject
{
    friend class QtReadabilityParserApi;

    Q_OBJECT

    Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)

public:
    bool loading();

protected:
    explicit ReadabilityArticleLoader(QUrl url, QtReadabilityParserApi* api);

signals:
    void articleReady(ReadabilityArticle* article);
    void loadingChanged();

public slots:
    void load();
    void onLoadingChanged();

private:
    ReadabilityArticle* m_article;
    QUrl m_url;
};

#endif // READABILITYARTICLELOADER_H
