#include "xmlparser.h"
#include <QFile>


#include <QDebug>

XmlParser::XmlParser(QObject *parent) : QObject(parent)
{

}

Scenario XmlParser::parseScenario()
{
    QFile file(":/scenario.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Open scenario.xml file failed";
        return Scenario{};
    }

    QXmlStreamReader xml(&file);

    Scenario scenario;

    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();

        if (xml.isStartElement())
        {
            if (xml.name() == "scenario")
                continue;

            if (xml.name() == "modules")
            {
//                qDebug() << "parse modlues";
                scenario.modules = parseModules(xml);
            }

            if (xml.name() == "formula")
            {
//                qDebug() << "parse formula";
                scenario.formula = parseFormula(xml);
            }
        }
    }

    file.close();

    return scenario;
}

QMap<QString, QString> XmlParser::parseModules(QXmlStreamReader &xml)
{
    QMap<QString, QString> modules;

    auto parseModule = [&xml, &modules]() {
        if (xml.isStartElement() && xml.name() == "module")
        {
            QString moduleName;
            QString modulePath;

            for (auto attr : xml.attributes())
            {
                if (attr.name().toString() == "name")
                    moduleName = attr.value().toString();

                if (attr.name().toString() == "path")
                    modulePath = attr.value().toString();
            }
            modules.insert(moduleName, modulePath);
        }
    };

    xml.readNext();
    while (!(xml.isEndElement() && xml.name() == "modules"))
    {
        parseModule();
        xml.readNext();
    }

    return modules;
}

Formula XmlParser::parseFormula(QXmlStreamReader &xml)
{
    Formula formula;

    auto parseArg = [&xml](){
        QString call = "";
        if (xml.isStartElement() && xml.name() == "moduleCall")
        {
            for (auto attr : xml.attributes())
            {
                if (attr.name().toString() == "call")
                    call = attr.value().toString();
            }
        }
        return call;
    };

    xml.readNext();
    xml.readNext();

    if (xml.isStartElement() && xml.name() == "plus")
    {
        formula.operation = OperationType::Plus;

        QList<QString> args;
        xml.readNext();
        while (!(xml.isEndElement() && xml.name() == "plus"))
        {
            QString arg = parseArg();
            if (!arg.isEmpty())
                args.append(arg);
            xml.readNext();
        }
        formula.args = args;
    }

    return formula;
}
