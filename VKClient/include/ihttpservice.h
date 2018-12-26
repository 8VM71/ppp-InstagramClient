#pragma once

#include <QObject>
#include <QMap>
#include <QString>
#include <functional>
#include <memory>

namespace network {

struct Response
{
    bool isError = false;
    QString errorString = "";
    int statusCode = 0;
    QByteArray data;
    QMap<QString, QString> headerData;
};

using ResponsePtr = std::shared_ptr<Response>;

using PerformCallback = std::function<void (ResponsePtr)>;

class IHttpService
{
public:
    virtual ~IHttpService() = default;

    virtual void getRequest(const QUrl &url, PerformCallback callback) = 0;
};

}

#define IHttpService_iid "com.VKClient.network.IHttpService/1.0"

Q_DECLARE_INTERFACE(network::IHttpService, IHttpService_iid)

