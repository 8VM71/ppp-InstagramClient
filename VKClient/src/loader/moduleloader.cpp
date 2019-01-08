#include "moduleloader.h"

#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QThread>
#include <algorithm>

#include <QCoreApplication>

using namespace loader;

ModuleLoader::ModuleLoader(QObject *parent)
    : QObject(parent)
    , m_httpService(nullptr)
{

}

void ModuleLoader::updateModules(const QMap<QString, QString> &modules)
{
    qDebug() << __FUNCTION__ << modules;

    m_modules.clear();
    for (auto key : modules.keys())
    {
        QString path = QCoreApplication::applicationDirPath() + "/" + modules.value(key);
        auto item = std::make_shared<ModuleItem>(key, path);
        item->setService(m_httpService);
        qDebug() << __FUNCTION__ << path;
        m_modules.append(item);
    }
}

void ModuleLoader::loadAll()
{
    for (auto module : m_modules)
    {
        qDebug() << __FUNCTION__ << module->getName();

        if (module->load())
        {
            qDebug() << module->getName() << "module load success";
        }
        else
        {
            qWarning() << module->getName() << "module load failed";
        }
    }
}

void ModuleLoader::setHttpService(HttpService *httpService)
{
    m_httpService = httpService;
}

ModuleItemPtr ModuleLoader::getModule(const QString &name)
{
    auto it = std::find_if(m_modules.begin(), m_modules.end(), [name](ModuleItemPtr item){
            return item && item->getName() == name;
    });

    return it != m_modules.end() ? *it
                                 : nullptr;
}
