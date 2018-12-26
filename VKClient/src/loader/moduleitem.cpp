#include "moduleitem.h"

#include "ivaluecalc.h"

using namespace loader;

ModuleItem::ModuleItem(const QString &path, QObject *parent)
    : QObject(parent)
    , m_path(path)
{
    m_loader.setFileName(m_path);
}

bool ModuleItem::load()
{
    if (m_loader.isLoaded())
        return true;

    return m_loader.load();
}

double ModuleItem::getValue(network::IHttpService *service)
{
    if (!m_loader.isLoaded())
        return 0;

    auto module = dynamic_cast<IValueCalc*>(m_loader.instance());

    return module ? module->calcValue(service) : 0;
}
