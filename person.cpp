#include "person.h"

Person::Person()
{
    this->name="name";
    this->address="address";
}
Person::Person(QString name, QString address)
{
    this->name=name;
    this->address=address;
}

Person::~Person()
{

}

QString Person::getName()
{
    return name;
}
void Person::setName(QString name)
{
    this->name=name;
}
QString Person::getAddress()
{
    return address;
}
void Person::setAddress(QString address)
{
    this->address=address;
}
QString Person::getPhone()
{
    return phone;
}
void Person::setPhone(QString phone)
{
    this->phone=phone;
}

quint8 Person::getAge()
{
    return age;
}
void Person::setAge(quint8 age)
{
    this->age=age;
}

QString Person::getData()
{
    return data;
}

void Person::setData(QString data)
{
    this->data=data;
}
