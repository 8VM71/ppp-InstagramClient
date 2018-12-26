#pragma once

#include <QObject>
#include <QPluginLoader>
#include "ihttpservice.h"

namespace loader {

class ModuleItem : public QObject
{
    Q_OBJECT
public:
    explicit ModuleItem(const QString& path, QObject *parent = nullptr);

    bool load();

    double getValue(network::IHttpService* service);

signals:

public slots:

private:
    QString m_path;
    QPluginLoader m_loader;
};

}

