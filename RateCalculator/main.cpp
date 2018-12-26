#include <QCoreApplication>

#include "receiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Receiver receiver;
    receiver.start();
    return a.exec();
}
