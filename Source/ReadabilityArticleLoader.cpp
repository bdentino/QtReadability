#include "ReadabilityArticleLoader.h"
#include "QtReadabilityApi.h"
#include "ReadabilityArticle.h"

ReadabilityArticleLoader::ReadabilityArticleLoader(QUrl url, QtReadabilityParserApi* api)
    : QObject(),
      m_article(new ReadabilityArticle(api)),
      m_url(url)
{
    connect(m_article, SIGNAL(loadingChanged()), this, SLOT(onLoadingChanged()));
}

bool ReadabilityArticleLoader::loading()
{
    return m_article->isLoading();
}

void ReadabilityArticleLoader::load()
{
    m_article->setUrl(m_url);
}

void ReadabilityArticleLoader::onLoadingChanged()
{
    if (!(m_article->isLoading()))
    {
        emit articleReady(m_article);
        deleteLater();
    }
    emit loadingChanged();
}

