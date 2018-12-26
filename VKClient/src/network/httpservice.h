#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <functional>
#include <memory>

#include "ihttpservice.h"

namespace network {

class HttpService : public QObject, public IHttpService
{
    Q_OBJECT
    Q_INTERFACES(network::IHttpService)
public:
    explicit HttpService(QObject *parent = nullptr);
    ~HttpService();

    void getRequest(const QUrl &url, PerformCallback callback);

private:
    void requestFunction(QNetworkReply * reply, PerformCallback callback);

private:
    QNetworkAccessManager m_manager;
    int m_waitTime;
};

}


