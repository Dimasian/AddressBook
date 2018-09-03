#ifndef FRIEND_H
#define FRIEND_H
#include <QString>
#include "person.h"

class Friend : public Person
{
public:
    Friend(QString name, QString address);
    QString getData();
    void setData(QString data);
private:
    //QString data;
};

#endif // FRIEND_H
