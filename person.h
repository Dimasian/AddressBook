#ifndef PERSON_H
#define PERSON_H
#include <QString>

class Person
{
public:
     Person();
     Person(QString name, QString address);
    ~Person();
     QString getName();
     void setName(QString name);
     QString getAddress();
     void setAddress(QString address);
     QString getPhone();
     void setPhone(QString phone);
     quint8 getAge();
     void setAge(quint8 age);

     // pure virtual method must be provided in subclass
     virtual QString getData();
     virtual void setData(QString data);

private:
    QString name;
    QString address;
    QString phone;
    quint8 age;
    QString data;
};

#endif // PERSON_H
