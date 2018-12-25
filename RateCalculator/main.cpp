#include <QCoreApplication>

#include "connectionhandler.h"

#include <amqpcpp.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ConnectionHandler handler;

//    // create a AMQP connection object
    AMQP::Connection connection(&handler, AMQP::Login("guest","guest"), "/");

    // and create a channel
    AMQP::Channel channel(&connection);

    // use the channel object to call the AMQP method you like
    channel.declareExchange("my-exchange", AMQP::fanout);
    channel.declareQueue("my-queue");
    channel.bindQueue("my-exchange", "my-queue", "my-routing-key");

    return a.exec();
}
