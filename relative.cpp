#include "relative.h"

Relative::Relative(QString name, QString address):Person(name,address)
{
    setData("I'm Relative class! I derive from Person!");
}

QString Relative::getData()
{
    return Person::getData();
}

void Relative::setData(QString data)
{
      Person::setData(data);
}
