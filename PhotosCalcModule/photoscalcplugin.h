#pragma once

#include <QObject>
#include <ivaluecalc.h>


class PhotosCalcPlugin : public QObject, public IValueCalc
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.PhotosCalcModule.PhotosCalcPlugin.IValueCalc")
    Q_INTERFACES(IValueCalc)
public:
    PhotosCalcPlugin(QObject *parent = nullptr);

    // IValueCalc interface
    double calcValue(network::IHttpService* service) override;
};

