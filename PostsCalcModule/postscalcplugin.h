#pragma once

#include <QObject>
#include <ivaluecalc.h>

class PostsCalcPlugin : public QObject, public IValueCalc
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.PostsCalcModule.PostsCalcPlugin.IValueCalc")
    Q_INTERFACES(IValueCalc)

public:
    PostsCalcPlugin(QObject *parent = nullptr);

    // IValueCalc interface
    double calcValue(network::IHttpService* service) override;
};

