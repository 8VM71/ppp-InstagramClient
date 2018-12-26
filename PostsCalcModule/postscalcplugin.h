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
    void setService(network::IHttpService *service) override;
    void setToken(const QString &token) override;
    void setUserId(const QString &id) override;
    void calcValue(PerformCallback callback) override;

private:
    RateEntity calcRate(const QJsonObject &data);

private:
    network::IHttpService* m_service;
    QString m_token;
    QString m_userId;
};

