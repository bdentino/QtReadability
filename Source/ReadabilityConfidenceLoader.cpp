#include "ReadabilityConfidenceLoader.h"
#include "QtReadabilityApi.h"
#include "ReadabilityConfidence.h"

ReadabilityConfidenceLoader::ReadabilityConfidenceLoader(QUrl url, QtReadabilityParserApi* api)
    : QObject(),
      m_confidence(new ReadabilityConfidence(api)),
      m_url(url)
{
    connect(m_confidence, SIGNAL(loadingChanged()), this, SLOT(onLoadingChanged()));
}

bool ReadabilityConfidenceLoader::loading()
{
    return m_confidence->isLoading();
}

void ReadabilityConfidenceLoader::load()
{
    m_confidence->setUrl(m_url);
}

void ReadabilityConfidenceLoader::onLoadingChanged()
{
    if (!(m_confidence->isLoading()))
    {
        emit confidenceReady(m_confidence);
        deleteLater();
    }
    emit loadingChanged();
}
