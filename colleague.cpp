#include "colleague.h"

Colleague::Colleague(QString name, QString address):Person(name,address)
{
   setData("I'm Colleague class! I derive from Person!");
}

QString Colleague::getData()
{
    return Person::getData();
}

void Colleague::setData(QString data)
{
    Person::setData(data);
}
