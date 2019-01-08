#pragma once

#include <QMap>
#include <QString>
#include <QVariantMap>

namespace entities {

struct RateEntity
{
    double rate = 0;
    QVariantMap data;
};

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
    /**
     * @brief modules
     * key - name
     * value - path
     */
    QMap<QString, QString> modules;

    Formula formula;
};

}
