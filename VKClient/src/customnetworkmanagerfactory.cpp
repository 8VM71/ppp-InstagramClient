#include "customnetworkmanagerfactory.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslError>

CustomNetworkManagerFactory::CustomNetworkManagerFactory(QObject *parent)
    : QObject(parent)
{

}

QNetworkAccessManager* CustomNetworkManagerFactory::create(QObject *parent)
{
    Q_UNUSED(parent)
    auto networkManager = new QNetworkAccessManager(this);

    connect(networkManager, &QNetworkAccessManager::sslErrors, [](QNetworkReply *reply, const QList<QSslError> &errors){
        reply->ignoreSslErrors(errors);
    });

    return networkManager;
}
