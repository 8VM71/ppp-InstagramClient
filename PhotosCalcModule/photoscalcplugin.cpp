#include "photoscalcplugin.h"
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonArray>
#include <algorithm>

#include <QDebug>

PhotosCalcPlugin::PhotosCalcPlugin(QObject *parent)
    : QObject (parent)
    , m_service(nullptr)
    , m_token("")
    , m_userId("")
{
}

void PhotosCalcPlugin::setService(network::IHttpService *service)
{
    m_service = service;
}

void PhotosCalcPlugin::setToken(const QString &token)
{
    m_token = token;
}

void PhotosCalcPlugin::setUserId(const QString &id)
{
    m_userId = id;
}

void PhotosCalcPlugin::calcValue(PerformCallback callback)
{
    qDebug() << __FUNCTION__;
    if (!m_service)
        callback(RateEntity{});

    QUrl requestUrl("https://api.vk.com/method/photos.getAll");

    QUrlQuery query;
    query.addQueryItem("owner_id", m_userId);
    query.addQueryItem("count", "100");
    query.addQueryItem("extended", "1");
    query.addQueryItem("v", "5.8");
    query.addQueryItem("access_token", m_token);

    requestUrl.setQuery(query);

    qDebug() << __FUNCTION__ << "url" << requestUrl.url();

    m_service->getRequest(requestUrl, [this, callback](network::ResponsePtr resp){
        if (resp->isError)
        {
            qDebug() << "PhotosCalcPlugin::calcValue Error:" << resp->errorString;
            callback(RateEntity{});
        }
        else
        {
            QJsonDocument doc = QJsonDocument::fromJson(resp->data);
            auto rate = this->calcRate(doc.object().value("response").toObject());
            callback(rate);
        }
    });
}

RateEntity PhotosCalcPlugin::calcRate(const QJsonObject &data)
{
    qDebug() << __FUNCTION__;

    int totalCount = data.value("count").toInt();

    auto items = data.value("items").toArray();

    int shownCount = items.size();

    int likes = std::accumulate(items.begin(), items.end(), 0, [](int sum, const QJsonValue &item){
        return sum + item.toObject().value("likes").toObject().value("count").toInt();
    });

    int reposts = std::accumulate(items.begin(), items.end(), 0, [](int sum, const QJsonValue &item){
        return sum + item.toObject().value("reposts").toObject().value("count").toInt();
    });

    int rate = shownCount > 0 ? ((likes + reposts) / shownCount ) * totalCount / shownCount
                              : 0;

    RateEntity re;
    re.rate = rate;
    re.data = {
        {"totalCount", totalCount},
        {"shownCount", shownCount},
        {"likes", likes},
        {"reposts", reposts},
    };

    return re;
}

