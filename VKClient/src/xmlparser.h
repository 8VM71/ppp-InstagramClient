#pragma once

#include <QObject>
#include <QXmlStreamReader>
#include <QMap>
#include <QString>

enum class OperationType
{
    Plus
};

struct Formula
{
    OperationType operation;
    QList<QString> args;
};

struct Scenario
{
    QMap<QString, QString> modules;
    Formula formula;
};

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
};
