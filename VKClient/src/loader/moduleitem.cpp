#include "moduleitem.h"

#include "ivaluecalc.h"

using namespace loader;

ModuleItem::ModuleItem(const QString &name, const QString &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
    , m_name(name)
    , m_service(nullptr)
{
    m_loader.setFileName(m_path);
}

bool ModuleItem::load()
{
    if (m_loader.isLoaded())
        return true;

    return m_loader.load();
}

void ModuleItem::getValue(const QString &userId, const QString &token, std::function<void(entities::RateEntity)> callback)
{
    if (!m_loader.isLoaded())
    {
        callback(RateEntity{});
        return;
    }

    auto module = dynamic_cast<IValueCalc*>(m_loader.instance());

    if (!module)
    {
        callback(RateEntity{});
        return;
    }

    module->setUserId(userId);
    module->setToken(token);
    module->setService(m_service);

    module->calcValue(callback);
}

QString ModuleItem::getName() const
{
    return m_name;
}

void ModuleItem::setName(const QString &name)
{
    m_name = name;
}

network::IHttpService *ModuleItem::getService() const
{
    return m_service;
}

void ModuleItem::setService(network::IHttpService *service)
{
    m_service = service;
}
