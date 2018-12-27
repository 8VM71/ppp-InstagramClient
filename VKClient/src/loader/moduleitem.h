#pragma once

#include <QObject>
#include <QPluginLoader>
#include <memory>
#include "ihttpservice.h"

namespace loader {

class ModuleItem : public QObject
{
    Q_OBJECT
public:
    explicit ModuleItem(const QString &name, const QString& path, QObject *parent = nullptr);

    bool load();

    double getValue(network::IHttpService* service);

    QString getName() const;
    void setName(const QString &name);

signals:

public slots:

private:
    QString m_path;
    QString m_name;
    QPluginLoader m_loader;
};

using ModuleItemPtr = std::shared_ptr<ModuleItem>;

}

