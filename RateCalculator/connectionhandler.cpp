#include "connectionhandler.h"

ConnectionHandler::ConnectionHandler()
{

}

void ConnectionHandler::onData(AMQP::Connection *connection, const char *data, size_t size)
{
    // @todo
    //  Add your own implementation, for example by doing a call to the
    //  send() system call. But be aware that the send() call may not
    //  send all data at once, so you also need to take care of buffering
    //  the bytes that could not immediately be sent, and try to send
    //  them again when the socket becomes writable again
}

void ConnectionHandler::onReady(AMQP::Connection *connection)
{
    // @todo
    //  add your own implementation, for example by creating a channel
    //  instance, and start publishing or consuming
}

void ConnectionHandler::onError(AMQP::Connection *connection, const char *message)
{
    // @todo
    //  add your own implementation, for example by reporting the error
    //  to the user of your program, log the error, and destruct the
    //  connection object because it is no longer in a usable state
}

void ConnectionHandler::onClosed(AMQP::Connection *connection)
{
    // @todo
    //  add your own implementation, for example by closing down the
    //  underlying TCP connection too
}
