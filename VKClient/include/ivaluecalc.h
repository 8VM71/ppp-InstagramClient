#pragma once

#include <QObject>
#include "ihttpservice.h"
#include <functional>
#include "entities.h"

using namespace entities;

using PerformCallback = std::function<void(RateEntity)>;

class IValueCalc
{
public:
    virtual ~IValueCalc() = default;

    virtual void setService(network::IHttpService* service) = 0;
    virtual void setToken(const QString &token) = 0;
    virtual void setUserId(const QString &id) = 0;

    virtual void calcValue(PerformCallback callback) = 0;

};

#define IValueCalc_iid "com.VKClient.IValueCalc/1.0"

Q_DECLARE_INTERFACE(IValueCalc, IValueCalc_iid)
