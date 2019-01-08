#pragma once

#include <QObject>
#include <QPluginLoader>
#include <memory>
#include "ihttpservice.h"
#include "entities.h"

namespace loader {

class ModuleItem : public QObject
{
    Q_OBJECT
public:
    explicit ModuleItem(const QString &name, const QString& path, QObject *parent = nullptr);

    bool load();

    void getValue(const QString& userId, const QString& token, std::function<void(entities::RateEntity)> callback);

    QString getName() const;
    void setName(const QString &name);

    network::IHttpService *getService() const;
    void setService(network::IHttpService *service);

signals:

public slots:

private:
    QString m_path;
    QString m_name;
    QPluginLoader m_loader;
    network::IHttpService* m_service;
};

using ModuleItemPtr = std::shared_ptr<ModuleItem>;

}

