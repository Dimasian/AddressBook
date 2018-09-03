#include "friend.h"

Friend::Friend(QString name, QString address):Person(name, address)
{
    setData("I'm Friend class! I derive from Person!");
}

QString Friend::getData()
{
    return Person::getData();
}

void Friend::setData(QString data)
{
    Person::setData(data);
}


