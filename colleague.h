#ifndef COLLEAGUE_H
#define COLLEAGUE_H
#include <QString>
#include "person.h"

class Colleague : public Person
{
public:
    Colleague(QString name, QString address);
    QString getData();
    void setData(QString data);
private:
    //QString data;
};

#endif // COLLEAGUE_H
