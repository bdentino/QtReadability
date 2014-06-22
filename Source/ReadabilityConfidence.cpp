#include "ReadabilityConfidence.h"

#include "QtReadabilityApi.h"
#include "ReadabilityHttpRequest.h"

ReadabilityConfidence::ReadabilityConfidence(QObject* parent)
    : QObject(parent),
      m_api(qobject_cast<QtReadabilityParserApi*>(parent)),
      m_request(NULL)
{
}

double ReadabilityConfidence::confidence() { return m_confidence; }

QUrl ReadabilityConfidence::url() { return m_url; }

QtReadabilityParserApi* ReadabilityConfidence::api() { return m_api; }

bool ReadabilityConfidence::isLoading() {
    if (m_request) return m_request->isLoading();
    else return false;
}

QString ReadabilityConfidence::error() { return m_error; }

void ReadabilityConfidence::setApi(QtReadabilityParserApi* api)
{
    if (m_api) {
        qWarning("Cannot change article API after initialization");
        return;
    }
    m_api = api;
    tryLoad();
}

void ReadabilityConfidence::setUrl(QUrl url)
{
    if (m_url == url)
        return;
    m_url = url;
    tryLoad();
}

void ReadabilityConfidence::tryLoad()
{
    if (!m_api) {
        m_error = "Cannot determine parse confidence (Invalid API Configuration)";
    }
    else if (!m_url.isValid()) {
        m_error = "Cannot determine parse confidence (Invalid URL)";
    }
    else {
        m_error.clear();
        if (m_request) {
            disconnect(m_request);
            m_request->disconnect(this);
            m_request->cancel();
            m_request->deleteLater();
        }

        m_request = m_api->getConfidenceRequest(m_url);
        connect(m_request, SIGNAL(responseReady(QJsonObject)),
                this, SLOT(onResponseReceived(QJsonObject)));
        connect(m_request, SIGNAL(requestError(QNetworkReply::NetworkError,QString)),
                this, SLOT(onRequestError(QNetworkReply::NetworkError,QString)));
        m_request->send();
    }
    emit loadingChanged();
    emit errorChanged(m_error);
}

void ReadabilityConfidence::onResponseReceived(QJsonObject response)
{
    fromJsonObject(m_api->parseConfidenceResponse(response));
}

void ReadabilityConfidence::onRequestError(QNetworkReply::NetworkError error, QString description)
{
    Q_UNUSED(error);
    qWarning("Readability Confidence Error: Failed to determine parse confidence for url '%s' (%s)",
             qPrintable(m_url.toString()),
             qPrintable(description));
    m_error = QString("Cannot determine parse confidence (%1)").arg(description);
    emit errorChanged(description);
}

void ReadabilityConfidence::fromJsonObject(QJsonObject description)
{
    m_url = QUrl(description["url"].toString());
    m_confidence = description["confidence"].toDouble();
    emit loadingChanged();
}
