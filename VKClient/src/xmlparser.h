#pragma once

#include <QObject>
#include <QXmlStreamReader>
#include <QMap>
#include <QString>

#include "entities/entities.h"

using namespace entities;

class XmlParser : public QObject
{
    Q_OBJECT
public:
    explicit XmlParser(QObject *parent = nullptr);

    Scenario parseScenario();

private:
    QMap<QString, QString> parseModules(QXmlStreamReader &xml);
    Formula parseFormula(QXmlStreamReader &xml);

private:
    QString m_scenarioPath;
};
