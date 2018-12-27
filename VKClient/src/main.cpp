#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "customnetworkmanagerfactory.h"

#include "loader/moduleloader.h"
#include "network/httpservice.h"
#include "xmlparser.h"

#include "ratecalculator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("YRGA");
    app.setOrganizationDomain("yrga.com");
    app.setApplicationName("User rate");

    QQmlApplicationEngine engine;

    CustomNetworkManagerFactory networkAccessManagerFactory(&app);

    loader::ModuleLoader loader;
    network::HttpService httpService;
    XmlParser xmlParser;

    auto scenario = xmlParser.parseScenario();

    loader.setHttpService(&httpService);

    RateCalculator calculator;

    calculator.setLoader(&loader);
    calculator.setScenario(scenario);

    engine.setNetworkAccessManagerFactory(&networkAccessManagerFactory);

    engine.rootContext()->setContextProperty("calculator", &calculator);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
