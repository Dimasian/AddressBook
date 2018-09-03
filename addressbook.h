#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QStackedLayout>
#include "person.h"
#include "finddialog.h"

class AddressBook : public QWidget
{
    Q_OBJECT
public:
    AddressBook(QWidget *parent = nullptr);
    ~AddressBook();
    enum Mode{NavigationMode, AddingMode, EditingMode};
    enum ContactType{None=0, Friends=1, Colleagues=2, Relatives=3};

    void AddPersonToQMap();

signals:

public slots:
    void contactTypeChanged();
    void addContact();
    void AddPersonToQMap(QString name, QString address);
    void submitContact();
    void cancel();
    void next();
    void previous();
    void editContact();
    void removeContact();
    void findContact();
    void saveToFile();
    void loadFromFile();

private:

    Person *prevPerson;
    ContactType currentType;
    Mode currentMode;
    QLineEdit *nameLine;
    QTextEdit *addressText;
    QMap<QString, Person*> contacts;

    //FindDialog *dialog;
    void updateInterface(Mode mode);
    FindDialog *dialog;

    QComboBox *contactTypeCombobox;
    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;
    QPushButton *loadButton;
    QPushButton *saveButton;

    QLabel *contactTypeLabel;
    QLabel *contactTypeLabelValue;


};

#endif // ADDRESSBOOK_H
