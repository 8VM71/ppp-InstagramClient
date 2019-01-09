#pragma once

#include <QObject>
#include "network/httpservice.h"
#include "moduleitem.h"

using namespace network;

namespace loader {

class ModuleLoader : public QObject
{
    Q_OBJECT
public:
    explicit ModuleLoader(QObject *parent = nullptr);

    void updateModules(const QMap<QString, QString> &modules);

    void loadAll();

    void setHttpService(IHttpService *httpService);

    ModuleItemPtr getModule(const QString& name);

signals:

public slots:

private:
    IHttpService* m_httpService;

    QList<ModuleItemPtr> m_modules;
};

}



