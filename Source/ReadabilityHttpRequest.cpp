#include "ReadabilityHttpRequest.h"

ReadabilityHttpRequest::ReadabilityHttpRequest(QUrl url, QObject* parent)
    : QObject(parent),
      m_url(url),
      m_pendingReply(NULL)
{
    connect(&m_requestManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onRequestFinished(QNetworkReply*)));
}

ReadabilityHttpRequest::~ReadabilityHttpRequest()
{
    if (m_pendingReply) m_pendingReply->abort();
}

QUrl ReadabilityHttpRequest::url()
{
    return m_url;
}

bool ReadabilityHttpRequest::isLoading()
{
    if (m_pendingReply) return m_pendingReply->isRunning();
    else return false;
}

void ReadabilityHttpRequest::cancel()
{
    if (!m_pendingReply) return;
    m_pendingReply->abort();
    emit loadingChanged(m_pendingReply->isRunning());
}

void ReadabilityHttpRequest::send()
{
    get(m_url);
}

void ReadabilityHttpRequest::get(QUrl url)
{
    setPendingReply(m_requestManager.get(QNetworkRequest(url)));
    connect(m_pendingReply, SIGNAL(metaDataChanged()), this, SLOT(redirectRequest()));
    connect(m_pendingReply, SIGNAL(error(QNetworkReply::NetworkError)),
            this, SLOT(onRequestError(QNetworkReply::NetworkError)));
}

void ReadabilityHttpRequest::setPendingReply(QNetworkReply* reply)
{
    if (m_pendingReply == reply) return;
    if (m_pendingReply)
    {
        m_pendingReply->disconnect(this);
        m_pendingReply->deleteLater();
    }
    m_pendingReply = reply;
    emit loadingChanged(m_pendingReply->isRunning());
}

void ReadabilityHttpRequest::redirectRequest()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply != m_pendingReply) return;

    QUrl redirectionTarget =
            reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
    qDebug("Readability Parser Request Info: Got Redirect Request to %s",
           qPrintable(redirectionTarget.toString()));
    if (redirectionTarget.isValid())
    {
        get(redirectionTarget);
    }
}

void ReadabilityHttpRequest::onRequestError(QNetworkReply::NetworkError error)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    if (reply != m_pendingReply) return;

    if (error != QNetworkReply::OperationCanceledError) {
        qWarning("Readability Parser Request Error: '%s'\n  Url: '%s'",
                 qPrintable(reply->errorString()),
                 qPrintable(m_pendingReply->url().toString()));

        emit requestError(error, reply->errorString());
    }
    emit loadingChanged(m_pendingReply->isRunning());
}

void ReadabilityHttpRequest::onRequestFinished(QNetworkReply* reply)
{
    if (reply != m_pendingReply) return;

    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode == 0)
    {
        emit loadingChanged(m_pendingReply->isRunning());
        return;
    }
    if (statusCode >= 200 && statusCode < 300)
    {
        QByteArray bytes = reply->readAll();
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);
        if (error.error != QJsonParseError::NoError)
        {
            qWarning("Readability Parser Request Error: Response could not be converted to JSON Object (%s)",
                     qPrintable(error.errorString()));
            emit requestError(QNetworkReply::ProtocolFailure, "Readability Parser Response Could Not Be Parsed.");
        }
        else
        {
            emit responseReady(doc.object());
        }
    }
    else
    {
        qWarning("Readability Parser Request Error: Unexpected Response Code %d returned from URL %s",
                    statusCode, qPrintable(m_url.toString()));
        emit requestError(QNetworkReply::UnknownNetworkError,
                          QString("Readability Parser Request Failed with Error Code %1").arg(statusCode));
    }
    emit loadingChanged(m_pendingReply->isRunning());
}
