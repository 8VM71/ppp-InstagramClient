#include "httpservice.h"
#include <QTimer>
#include <QDebug>
#include <QLoggingCategory>

using namespace network;

HttpService::HttpService(QObject *parent)
    : QObject(parent)
    , m_waitTime(5 * 60 * 1000)
{
}

HttpService::~HttpService()
{
}


void HttpService::getRequest(const QUrl &url, PerformCallback callback)
{
    QNetworkRequest request;
    request.setUrl(url);

    auto reply = m_manager.get(request);
    requestFunction(reply, callback);
}

void HttpService::requestFunction(QNetworkReply *reply, PerformCallback callback)
{
    if (reply == nullptr)
    {
        ResponsePtr resp = std::make_shared<Response>();
        resp->isError = true;
        resp->errorString = "Reply is nullptr";
        callback(resp);
        return;
    }

    std::shared_ptr<QTimer> timer = std::make_shared<QTimer>();

    timer->setInterval(m_waitTime);
    timer->setSingleShot(true);

    connect(timer.get(), &QTimer::timeout, reply, &QNetworkReply::abort);
    connect(reply, &QNetworkReply::readyRead, timer.get(), &QTimer::stop);

    timer->start();

    connect(reply, &QNetworkReply::finished, [reply, timer, callback] (){
        timer->stop();

        ResponsePtr response = std::make_shared<Response>();

        if (reply == nullptr)
        {
            response->isError = true;
            response->errorString = "Reply is nullptr";
            callback(response);
            return;
        }

        if (reply->error() != QNetworkReply::NoError)
        {
            response->isError = true;
            response->errorString = reply->errorString();
        }
        else
        {
            response->statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
            for (auto it : reply->rawHeaderPairs())
            {
                QString name(it.first);
                QString data(it.second);
                response->headerData.insert(name, data);
            }
            response->data = reply->readAll();
        }
        callback(response);
        reply->deleteLater();
    });
}
