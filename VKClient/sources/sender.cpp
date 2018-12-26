#include "sender.h"

#include <QJsonDocument>
#include <QJsonObject>

Sender::Sender(QObject *parent)
    : QObject(parent)
    , m_queueName("userrate")
    , m_valid(false)
{

}

Sender::~Sender()
{
    m_client.disconnectFromHost();
}

bool Sender::valid() const
{
    return m_valid;
}

void Sender::start()
{
    m_client.connectToHost();

    connect(dynamic_cast<QObject*>(&m_client), SIGNAL(connected()), this, SLOT(clientConnected()));
    connect(dynamic_cast<QObject*>(&m_client), SIGNAL(disconnected()), this, SLOT(connectionClosed()));
}

void Sender::sendMessage(const QJsonObject &obj)
{
    if(!valid())
        return;

    QAmqpExchange *defaultExchange = m_client.createExchange();

    QString str(QJsonDocument(obj).toJson());

    defaultExchange->publish(str, m_queueName);
    qDebug().noquote() << " [x] Sent:" << str;
}

void Sender::setValid(bool valid)
{
    if (m_valid == valid)
        return;

    m_valid = valid;
    emit validChanged(m_valid);
}

void Sender::clientConnected()
{
    qDebug() << __FUNCTION__;

    queue = m_client.createQueue(m_queueName);
    connect(dynamic_cast<QObject*>(queue), SIGNAL(declared()), this, SLOT(queueDeclared()));
    queue->declare();
}

void Sender::connectionClosed()
{
    setValid(false);
}

void Sender::queueDeclared()
{
    qDebug() << __FUNCTION__;
    setValid(true);

    connect(dynamic_cast<QObject*>(queue), SIGNAL(messageReceived()), this, SLOT(messageReceived()));
    queue->consume(QAmqpQueue::coNoAck);
}

void Sender::messageReceived()
{
    QAmqpMessage message = queue->dequeue();
    QString data = message.payload();
    qDebug() << " [x] Received:" << data;

    emit userRateCalculated(data.toDouble());
}
