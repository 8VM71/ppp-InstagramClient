#ifndef CUSTOMNETWORKMANAGERFACTORY_H
#define CUSTOMNETWORKMANAGERFACTORY_H

#include <QObject>
#include <QQmlNetworkAccessManagerFactory>

class CustomNetworkManagerFactory : public QObject, public QQmlNetworkAccessManagerFactory
{
    Q_OBJECT

public:
    explicit CustomNetworkManagerFactory(QObject *parent = nullptr);
    virtual QNetworkAccessManager *create(QObject *parent) override;

};

#endif // CUSTOMNETWORKMANAGERFACTORY_H
