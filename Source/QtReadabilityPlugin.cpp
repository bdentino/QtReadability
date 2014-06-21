#include "QtReadabilityPlugin.h"
#include "QtReadabilityApi.h"
#include "ReadabilityArticle.h"
#include "ReadabilityConfidence.h"

#include <qqml.h>

void QtReadabilityPlugin::registerTypes(const char* uri)
{
    // @uri Qtino.Readability
    qmlRegisterType<QtReadabilityParserApi>(uri, 1, 0, "ReadabilityParserApi");
    qmlRegisterType<ReadabilityArticle>(uri, 1, 0, "ReadabilityArticle");
    qmlRegisterType<ReadabilityConfidence>(uri, 1, 0, "ReadabilityConfidence");
}
