#include "photoscalcplugin.h"


PhotosCalcPlugin::PhotosCalcPlugin(QObject *parent)
    : QObject (parent)
{
}

double PhotosCalcPlugin::calcValue(network::IHttpService *service)
{
    return 5;
}
