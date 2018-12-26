#ifndef SENDER_H
#define SENDER_H

#include <QObject>

#include <QTimer>
#include <QDebug>
#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"

class Sender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool valid READ valid WRITE setValid NOTIFY validChanged)

public:
    explicit Sender(QObject *parent = nullptr);
    ~Sender();

    bool valid() const;
    void setValid(bool valid);

public slots:
    void start();
    void sendMessage(const QJsonObject &obj);

signals:
    void validChanged(bool valid);
    void userRateCalculated(double rate);

private slots:
    void clientConnected();
    void connectionClosed();
    void queueDeclared();
    void messageReceived();

private:
    QAmqpClient m_client;
    QString m_queueName;
    QAmqpQueue *queue;
    QAmqpExchange *defaultExchange;

    bool m_valid;
};

#endif // SENDER_H
