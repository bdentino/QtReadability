#include "ReadabilityArticle.h"

#include "QtReadabilityApi.h"
#include "ReadabilityHttpRequest.h"

ReadabilityArticle::ReadabilityArticle(QObject* parent)
    : QObject(parent),
      m_api(qobject_cast<QtReadabilityParserApi*>(parent)),
      m_request(NULL)
{
}

QtReadabilityParserApi* ReadabilityArticle::api() { return m_api; }

QString ReadabilityArticle::htmlContent() { return m_htmlContent; }

QUrl ReadabilityArticle::domain() { return m_domain; }

QString ReadabilityArticle::author() { return m_author; }

QUrl ReadabilityArticle::url() { return m_url; }

QUrl ReadabilityArticle::shortUrl() { return m_shortUrl; }

QString ReadabilityArticle::title() { return m_title; }

QString ReadabilityArticle::htmlExcerpt() { return m_htmlExcerpt; }

Qt::LayoutDirection ReadabilityArticle::direction() { return m_direction; }

int ReadabilityArticle::wordCount() { return m_wordCount; }

int ReadabilityArticle::totalPages() { return m_totalPages; }

QDateTime ReadabilityArticle::publishedDate() { return m_publishedDate; }

QString ReadabilityArticle::htmlDek() { return m_htmlDek; }

QUrl ReadabilityArticle::leadImageSource() { return m_leadImageSource; }

QString ReadabilityArticle::nextPageId() { return m_nextPageId; }

int ReadabilityArticle::parsedPages() { return m_parsedPages; }

bool ReadabilityArticle::isLoading() {
    if (m_request) return m_request->isLoading();
    else return false;
}

QString ReadabilityArticle::error() { return m_error; }

void ReadabilityArticle::setApi(QtReadabilityParserApi* api)
{
    if (m_api) {
        qWarning("Cannot change article API after initialization");
        return;
    }
    m_api = api;
    tryLoad();
}

void ReadabilityArticle::setUrl(QUrl url)
{
    if (m_url == url)
        return;
    m_url = url;
    tryLoad();
}

void ReadabilityArticle::tryLoad()
{
    if (!m_api) {
        m_error = "Cannot access article content (Invalid API Configuration)";
    }
    else if (!m_url.isValid()) {
        m_error = "Cannot access article content (Invalid URL)";
    }
    else {
        m_error.clear();
        if (m_request) {
            disconnect(m_request);
            m_request->disconnect(this);
            m_request->cancel();
            m_request->deleteLater();
        }

        m_request = m_api->getParseRequest(m_url);
        connect(m_request, SIGNAL(responseReady(QJsonObject)),
                this, SLOT(onResponseReceived(QJsonObject)));
        connect(m_request, SIGNAL(requestError(QNetworkReply::NetworkError,QString)),
                this, SLOT(onRequestError(QNetworkReply::NetworkError,QString)));
        m_request->send();
    }
    emit loadingChanged();
    emit errorChanged(m_error);
}

void ReadabilityArticle::onResponseReceived(QJsonObject response)
{
    fromJsonObject(m_api->parseArticleResponse(response));
}

void ReadabilityArticle::onRequestError(QNetworkReply::NetworkError error, QString description)
{
    Q_UNUSED(error);
    qWarning("Readability Article Error: Failed to parse url '%s' (%s)",
             qPrintable(m_url.toString()),
             qPrintable(description));
    m_error = QString("Cannot access article content (%1)").arg(description);
    emit errorChanged(description);
}

void ReadabilityArticle::fromJsonObject(QJsonObject description)
{
    m_htmlContent = description["content"].toString();
    m_domain = QUrl(description["domain"].toString());
    m_author = description["author"].toString();
    m_url = QUrl(description["url"].toString());
    m_shortUrl = QUrl(description["short_url"].toString());
    m_title = description["title"].toString();
    m_htmlExcerpt = description["excerpt"].toString();
    QString direction = description["direction"].toString();
    m_direction = (direction == "rtl" ? Qt::RightToLeft : Qt::LeftToRight);
    m_wordCount = description["word_count"].toInt();
    m_totalPages = description["total_pages"].toInt();
    m_publishedDate = QDateTime::fromString(
                description["date_published"].toString(),
            "yyyy-MM-dd hh:mm:ss");
    m_htmlDek = description["dek"].toString();
    m_leadImageSource = QUrl(description["lead_image_url"].toString());

    //TODO: Need to figure out what 'next_page_id' looks like...not documented very well
    //      by Readability...
    m_nextPageId = description["next_page_id"].toInt();
    m_parsedPages = description["rendered_pages"].toInt();

    emit loadingChanged();
}
