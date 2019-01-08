#include "ratecalculator.h"


#include <QDebug>

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
    if (!m_loader)
        return;

    m_loader->updateModules(m_scenario.modules);
    m_loader->loadAll();

    Formula formula = m_scenario.formula;

    m_totalArgs = formula.args.length();
    m_currentArg = 0;

    m_currentUserId = userId;
    m_token = token;

    setUserRate(0);

    calcNext();
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

void RateCalculator::calcNext()
{
    auto args = m_scenario.formula.args;

    if (m_currentArg < 0 || m_currentArg >= args.length())
        return;

    QString currentModuleName = args[m_currentArg];

    auto moduleItem = m_loader->getModule(currentModuleName);

    if (!moduleItem)
        return;

    m_currentArg++;

    moduleItem->getValue(m_currentUserId, m_token, [this, moduleItem](RateEntity re){

        qDebug() << "RateCalculator::calcNext" << re.rate << re.data;

        if (moduleItem->getName() == "PhotosCalcModule")
        {
            this->setPhotosData(re.data);
        }
        else if (moduleItem->getName() == "PostsCalcModule") {
            this->setPostsData(re.data);
        }

        if (m_scenario.formula.operation == OperationType::Plus)
        {
            this->setUserRate(m_userRate + re.rate);
        }

        calcNext();
    });
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
