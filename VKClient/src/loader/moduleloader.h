#pragma once

#include <QObject>
#include "network/httpservice.h"

using namespace network;

namespace loader {

class ModuleLoader : public QObject
{
    Q_OBJECT
public:
    explicit ModuleLoader(QObject *parent = nullptr);

    QString moduleDirPath() const;
    void setModuleDirPath(const QString &moduleDirPath);

    void load();

    void setHttpService(HttpService *httpService);

signals:

public slots:

private:
    QString m_moduleDirPath;
    HttpService* m_httpService;
};

}



