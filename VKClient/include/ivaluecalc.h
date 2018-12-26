#pragma once

#include <QObject>
#include "ihttpservice.h"

class IValueCalc
{
public:
    virtual ~IValueCalc() = default;
    virtual double calcValue(network::IHttpService* service) = 0;
};

#define IValueCalc_iid "com.VKClient.IValueCalc/1.0"

Q_DECLARE_INTERFACE(IValueCalc, IValueCalc_iid)
