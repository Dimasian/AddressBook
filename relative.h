#ifndef RELATIVE_H
#define RELATIVE_H
#include <QString>
#include "person.h"

class Relative : public Person
{
public:
    Relative(QString name, QString address);
    QString getData();
    void setData(QString data);
private:
    //QString data;
};

#endif // RELATIVE_H
