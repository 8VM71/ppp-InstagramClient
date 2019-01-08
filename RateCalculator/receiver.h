#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>

#include <QTimer>
#include <QDebug>
#include "qamqpclient.h"
#include "qamqpexchange.h"
#include "qamqpqueue.h"

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
    ~Receiver();

signals:

public slots:
    void start();

private slots:

    void clientConnected();

    void queueDeclared();

    void messageReceived();

    void sendMessage(const QString& message);

private:
    double calcRate(const QString& data);

private:
    QAmqpClient m_client;
    QString m_queueName;
};

#endif // RECEIVER_H
