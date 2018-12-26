#include "postscalcplugin.h"


PostsCalcPlugin::PostsCalcPlugin(QObject *parent) :
    QObject (parent)
{
}

double PostsCalcPlugin::calcValue(network::IHttpService *service)
{
    return 10;
}

