#ifndef RATECALCULATOR_H
#define RATECALCULATOR_H

#include <QObject>
#include <QVariantMap>
#include "loader/moduleloader.h"
#include "xmlparser.h"

class RateCalculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantMap photosData READ photosData WRITE setPhotosData NOTIFY photosDataChanged)
    Q_PROPERTY(QVariantMap postsData READ postsData WRITE setPostsData NOTIFY postsDataChanged)
    Q_PROPERTY(double userRate READ userRate WRITE setUserRate NOTIFY userRateChanged)
public:
    explicit RateCalculator(QObject *parent = nullptr);

    QVariantMap postsData() const;

    QVariantMap photosData() const;

    double userRate() const;

    void setScenario(const Scenario &scenario);

    void setLoader(loader::ModuleLoader *loader);

signals:

    void postsDataChanged(QVariantMap postsData);

    void photosDataChanged(QVariantMap photosData);

    void userRateChanged(double userRate);

public slots:
    void calcRate(const QString &userId, const QString &token);
    void setPostsData(QVariantMap postsData);

    void setPhotosData(QVariantMap photosData);

    void setUserRate(double userRate);

private:

    QVariantMap m_postsData;
    QVariantMap m_photosData;
    double m_userRate;

    loader::ModuleLoader *m_loader;
    Scenario m_scenario;
};

#endif // RATECALCULATOR_H
