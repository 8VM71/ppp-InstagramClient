#include "receiver.h"

#include <QJsonDocument>
#include <QJsonObject>

Receiver::Receiver(QObject *parent)
    : QObject(parent)
    , m_queueName("userrate")
{
    m_client.setAutoReconnect(true);
}

Receiver::~Receiver()
{
    m_client.disconnectFromHost();
}

void Receiver::start()
{
    connect(dynamic_cast<QObject*>(&m_client), SIGNAL(connected()), this, SLOT(clientConnected()));
    m_client.connectToHost();
}

void Receiver::clientConnected()
{
    qDebug() << __FUNCTION__;
    QAmqpQueue *queue = m_client.createQueue(m_queueName);
    connect(dynamic_cast<QObject*>(queue), SIGNAL(declared()), this, SLOT(queueDeclared()));
    queue->declare();
}

void Receiver::queueDeclared()
{
    qDebug() << __FUNCTION__;
    QAmqpQueue *queue = dynamic_cast<QAmqpQueue*>(sender());
    if (!queue)
        return;

    connect(dynamic_cast<QObject*>(queue), SIGNAL(messageReceived()), this, SLOT(messageReceived()));
    queue->consume(QAmqpQueue::coNoAck);
    qDebug() << " [*] Waiting for messages. To exit press CTRL+C";
}

void Receiver::messageReceived()
{
    qDebug() << __FUNCTION__;
    QAmqpQueue *queue = dynamic_cast<QAmqpQueue*>(sender());
    if (!queue)
        return;

    QAmqpMessage message = queue->dequeue();
    QString data = message.payload();
    qInfo() << " [x] Received:" << qPrintable(data);

    double rate = calcRate(data);

    QAmqpExchange *defaultExchange = m_client.createExchange();
    defaultExchange->publish(QString::number(rate), m_queueName);

    qDebug() << " [x] Sent:" << rate;
}

double Receiver::calcRate(const QString &data)
{
    QJsonObject obj(QJsonDocument::fromJson(data.toLocal8Bit()).object());

    double photoRate = 0;
    {
        QJsonObject photos = obj.value("photos").toObject();
        int totalCount = photos.value("totalCount").toInt();
        int shownCount = photos.value("shownCount").toInt();
        int likes = photos.value("likes").toInt();
        int reposts = photos.value("reposts").toInt();

        if(shownCount > 0)
            photoRate = ((likes + reposts) / shownCount ) * totalCount / shownCount;
    }

    double postsRate = 0.0;
    {
        QJsonObject posts = obj.value("posts").toObject();
        int totalCount = posts.value("totalCount").toInt();
        int shownCount = posts.value("shownCount").toInt();
        int likes = posts.value("likes").toInt();
        int reposts = posts.value("reposts").toInt();
        int comments = posts.value("comments").toInt();

        if(shownCount > 0)
            postsRate = ((likes + reposts + comments) / shownCount ) * totalCount / shownCount;
    }

    return photoRate + postsRate;
}
















