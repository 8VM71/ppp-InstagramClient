#pragma once

#include <QMap>
#include <QString>

namespace entities {

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
