#include "ratecalculator.h"

RateCalculator::RateCalculator(QObject *parent) : QObject(parent)
{
}

QVariantMap RateCalculator::postsData() const
{
    return m_postsData;
}

QVariantMap RateCalculator::photosData() const
{
    return m_photosData;
}

double RateCalculator::userRate() const
{
    return m_userRate;
}

void RateCalculator::calcRate(const QString &userId, const QString &token)
{
    //TODO implement
}

void RateCalculator::setPostsData(QVariantMap postsData)
{
    if (m_postsData == postsData)
        return;

    m_postsData = postsData;
    emit postsDataChanged(m_postsData);
}

void RateCalculator::setPhotosData(QVariantMap photosData)
{
    if (m_photosData == photosData)
        return;

    m_photosData = photosData;
    emit photosDataChanged(m_photosData);
}

void RateCalculator::setUserRate(double userRate)
{
//    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_userRate, userRate))
        return;

    m_userRate = userRate;
    emit userRateChanged(m_userRate);
}

void RateCalculator::setLoader(loader::ModuleLoader *loader)
{
    m_loader = loader;
}

void RateCalculator::setScenario(const Scenario &scenario)
{
    m_scenario = scenario;
    if (m_loader)
        m_loader->updateModules(m_scenario.modules);
}
