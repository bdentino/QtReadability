#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "QtReadabilityApi.h"
#include "ReadabilityArticle.h"
#include "ReadabilityConfidence.h"

int main(int argc, char *argv[])
{
    ReadabilityApiVersion apiVersion("v1");
    QtReadabilityParserApi parser(apiVersion, "<api_token>");

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("contextArticle", new ReadabilityArticle(&parser));
    engine.rootContext()->setContextProperty("contextConfidence", new ReadabilityConfidence(&parser));
    engine.load(QUrl(QStringLiteral("qrc:///main.qml")));

    return app.exec();
}
