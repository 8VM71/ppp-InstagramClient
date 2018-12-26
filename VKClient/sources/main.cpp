#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "customnetworkmanagerfactory.h"

#include "sender.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("YRGA");
    app.setOrganizationDomain("yrga.com");
    app.setApplicationName("User rate");   

    QQmlApplicationEngine engine;
    CustomNetworkManagerFactory networkAccessManagerFactory(&app);
    engine.setNetworkAccessManagerFactory(&networkAccessManagerFactory);

    Sender sender;
    engine.rootContext()->setContextProperty("sender", &sender);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
