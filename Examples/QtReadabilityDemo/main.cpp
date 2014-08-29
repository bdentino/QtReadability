#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QtReadabilityApi.h"
#include "ReadabilityArticle.h"
#include "ReadabilityConfidence.h"

// The file "ApiToken.h" doesn't exist in the repo. You need to create it and
// define the following variable using the value provided by the Readability
// organization in order to use their API in your application:
//
//   //ApiToken.h
//   #define READABILITY_API_TOKEN <your_api_token_string>
#include "ApiToken.h"

int main(int argc, char *argv[])
{
    ReadabilityApiVersion apiVersion("v1");
    QtReadabilityParserApi parser(apiVersion, QByteArray(READABILITY_API_TOKEN));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("contextArticle", new ReadabilityArticle(&parser));
    engine.rootContext()->setContextProperty("contextConfidence", new ReadabilityConfidence(&parser));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
