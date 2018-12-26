#include "moduleloader.h"

#include <QDir>
#include <QFileInfo>
#include <QDebug>

#include "moduleitem.h"

using namespace loader;

ModuleLoader::ModuleLoader(QObject *parent)
    : QObject(parent)
    , m_httpService(nullptr)
{

}

QString ModuleLoader::moduleDirPath() const
{
    return m_moduleDirPath;
}

void ModuleLoader::setModuleDirPath(const QString &moduleDirPath)
{
    m_moduleDirPath = moduleDirPath;
}

void ModuleLoader::load()
{
    QDir moduleDir(m_moduleDirPath);

    for (auto moduleName : moduleDir.entryInfoList(QDir::Files))
    {
        if (moduleName.suffix() != "dll")
            continue;

        ModuleItem module(moduleName.absoluteFilePath());
        if (module.load())
        {
            qDebug() << moduleName.baseName() << "value" << module.getValue(m_httpService);
        }
    }
}

void ModuleLoader::setHttpService(HttpService *httpService)
{
    m_httpService = httpService;
}
