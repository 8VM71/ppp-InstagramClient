#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "customnetworkmanagerfactory.h"

#include <QDebug>


#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"

class Sender : public QObject
{
    Q_OBJECT
public:
    Sender(QObject *parent = nullptr) : QObject(parent) {}

public Q_SLOTS:
    void start() {
        connect(&m_client, SIGNAL(connected()), this, SLOT(clientConnected()));
        connect(&m_client, SIGNAL(disconnected()), qApp, SLOT(quit()));
        m_client.connectToHost();
    }

private Q_SLOTS:
    void clientConnected() {
        QAmqpQueue *queue = m_client.createQueue("hello");
        connect(queue, SIGNAL(declared()), this, SLOT(queueDeclared()));
        queue->declare();
    }

    void queueDeclared() {
        QAmqpQueue *queue = qobject_cast<QAmqpQueue*>(sender());
        if (!queue)
            return;
        QAmqpExchange *defaultExchange = m_client.createExchange();
        defaultExchange->publish("Hello World!", "hello");
        qDebug() << " [x] Sent 'Hello World!'";
        m_client.disconnectFromHost();
    }

private:
    QAmqpClient m_client;

};


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("YRGA");
    app.setOrganizationDomain("yrga.com");
    app.setApplicationName("User rate");

    Sender sender;
    sender.start();

    QQmlApplicationEngine engine;
    CustomNetworkManagerFactory networkAccessManagerFactory(&app);
    engine.setNetworkAccessManagerFactory(&networkAccessManagerFactory);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
