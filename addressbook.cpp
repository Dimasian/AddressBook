
#include <QStackedLayout>
#include <QDebug>
//#include <QStackedWidget>
#include <QGridLayout>
#include <QMessageBox>
#include<QFileDialog>
#include "addressbook.h"
#include "person.h"
#include "friend.h"
#include "colleague.h"
#include "relative.h"

AddressBook::AddressBook(QWidget *parent) : QWidget(parent)
{
    prevPerson=new Person();

    //----- создаем лейблы--------
    QLabel *nameLabel=new QLabel(tr("Name:"));
    QLabel *addressLabel=new QLabel(tr("Address:"));
    //    QLabel *phoneLabel=new QLabel(tr("Phone:"));
    //    QLabel *ageLabel=new QLabel(tr("Age:"));
    contactTypeLabel=new QLabel(tr("Type:"));
    contactTypeLabelValue=new QLabel(tr("Friend/Colleague/Family"));

    //----- инициализируем поля ввода--------
    nameLine=new QLineEdit;
    nameLine->setReadOnly(true);

    addressText=new QTextEdit;
    addressText->setReadOnly(true);

    //------- добавляем кнопки-----------
    contactTypeCombobox=new QComboBox();
    contactTypeCombobox->addItem("SELECT TYPE",ContactType::None);
    contactTypeCombobox->addItem("Friend",ContactType::Friends);
    contactTypeCombobox->addItem("Colleague",ContactType::Colleagues);
    contactTypeCombobox->addItem("Relative",ContactType::Relatives);

    addButton = new QPushButton(tr("&Add"));
    addButton->setEnabled(false);
    addButton->show();
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();

    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);

    nextButton=new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton=new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);

    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);
    dialog=new FindDialog;

    loadButton=new QPushButton(tr("&Load..."));
    loadButton->setToolTip(tr("Load contacts from a file"));
    saveButton=new QPushButton(tr("&Save..."));
    saveButton->setToolTip(tr("Save contacts to a file"));

    //------- коннектим сигналы и слоты----------------------------------
    connect(contactTypeCombobox,SIGNAL(currentIndexChanged(int)),this,SLOT(contactTypeChanged()));

    connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
    connect(submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(previous()));

    connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));

    connect(findButton, SIGNAL(clicked()), this, SLOT(findContact()));

    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadFromFile()));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveToFile()));

    //---------- размещаем кнопки на лэйаут-----------------------
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(contactTypeCombobox, Qt::AlignTop);
    buttonLayout1->addWidget(addButton);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addWidget(findButton);
    buttonLayout1->addWidget(loadButton);
    buttonLayout1->addWidget(saveButton);
    buttonLayout1->addStretch();

    QHBoxLayout *buttonLayout2=new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);

    // ---- Объединяем кнопки в одном лейауте
    QVBoxLayout *buttonsLayout=new QVBoxLayout;
    buttonsLayout->addLayout(buttonLayout1);
    buttonsLayout->addLayout(buttonLayout2);

    //-------------Grid-Лэйаут для общих данных класса Person-------------------
    QGridLayout *personDataLayout=new QGridLayout;
    personDataLayout->addWidget(nameLabel, 0, 0);
    personDataLayout->addWidget(nameLine, 0, 1);
    personDataLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    personDataLayout->addWidget(addressText, 1, 1);

    //-------------Лэйаут по конкретному типу (Friend)------
    QGridLayout *friendDataLayout=new QGridLayout;
    friendDataLayout->addWidget(contactTypeLabel, 0, 0);
    friendDataLayout->addWidget(contactTypeLabelValue, 0, 1);
    // wrapping layout in a widget to add later to QStackedLayout
    QWidget *friendWidget=new QWidget();
    friendWidget->setLayout(friendDataLayout);


    //-------------Лэйаут по конкретному типу (Colleague)------
    QGridLayout *colleagueDataLayout=new QGridLayout;
    colleagueDataLayout->addWidget(contactTypeLabel, 0, 0);
    colleagueDataLayout->addWidget(contactTypeLabelValue, 0, 1);
    // wrapping layout in a widget to add later to QStackedLayout
    QWidget *colleagueWidget=new QWidget();
    colleagueWidget->setLayout(colleagueDataLayout);

    //-------------Лэйаут по конкретному типу (Family)------
    QGridLayout *familyDataLayout=new QGridLayout;
    familyDataLayout->addWidget(contactTypeLabel, 0, 0);
    familyDataLayout->addWidget(contactTypeLabelValue, 0, 1);
    // wrapping layout in a widget to add later to QStackedLayout
    QWidget *familyWidget=new QWidget();
    familyWidget->setLayout(familyDataLayout);


    //----Стек-Лэйаут для накладывающихся виджетов (Friend, Colleague, Family)----
    QStackedLayout *stackedLayout=new QStackedLayout;
    stackedLayout->addWidget(friendWidget);
    stackedLayout->addWidget(colleagueWidget);
    stackedLayout->addWidget(familyWidget);
    stackedLayout->setCurrentIndex(0);// set current widget


    //----Общий бокс для данных Person + Friend/Colleague/Family
    QVBoxLayout * dataLayout=new QVBoxLayout;
    dataLayout->addLayout(personDataLayout);
    dataLayout->addLayout(stackedLayout);

    //--Главный лейаут. Слева - дата, справа -кнопки.------
    QHBoxLayout * mainLayout=new QHBoxLayout;
    mainLayout->addLayout(dataLayout);
    mainLayout->addLayout(buttonsLayout);

    // устанавливаем лэйаут для виджета
    setLayout(mainLayout);
    setWindowTitle(tr("MartiD Address Book"));
}


AddressBook::~AddressBook()
{


}

// Возможность создать новый контакт появляется после выбора типа контакта
void AddressBook::contactTypeChanged()
{
    //currentType=ContactType(contactTypeCombobox->currentData().toInt());// Friend/Colleague/Family
    switch (contactTypeCombobox->currentIndex())
    {
    case 0:
    {
        currentType=ContactType::None;
        break;
    }
    case 1:
    {
        currentType=ContactType::Friends;
        break;
    }
    case 2:
    {
        currentType=ContactType::Colleagues;
        break;
    }
    case 3:
    {
        currentType=ContactType::Relatives;
        break;
    }
    default:
    {
        break;
    }
    }


    if(currentType!=ContactType::None)
    {
        addButton->setEnabled(true);
    }
    else
    {
        addButton->setEnabled(false);
    }

}

void AddressBook::addContact()
{

    prevPerson->setName(nameLine->text());
    prevPerson->setAddress(addressText->toPlainText());

    nameLine->clear();
    addressText->clear();
    updateInterface(AddingMode);
}

void AddressBook::editContact()
{
    prevPerson->setName(nameLine->text());
    prevPerson->setAddress(addressText->toPlainText());
    updateInterface(EditingMode);
}

void AddressBook::AddPersonToQMap(QString name, QString address)
{
    switch (currentType)
    {

        case ContactType::Friends:
        {
            Friend *frnd=new Friend(name, address);
            contacts.insert(frnd->getName(),frnd);
            break;
        }
        case ContactType::Colleagues:
        {
            Colleague *colleague=new Colleague(name, address);
            contacts.insert(colleague->getName(),colleague);
            break;
        }
        case ContactType::Relatives:
        {
            Relative *relative=new Relative(name, address);
            contacts.insert(relative->getName(),relative);
            break;
        }
        default:
        {
            break;
        }
    }
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (name == "" || address == "")
    {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name and address."));
    }

    if (currentMode == AddingMode) {

        if (!contacts.contains(name))
        {
            AddPersonToQMap(nameLine->text(), addressText->toPlainText());
            QMessageBox::information(this, tr("Add Successful"),
                tr("\"%1\" has been added to your address book.").arg(name));
        }
        else
        {
            QMessageBox::information(this, tr("Add Unsuccessful"),
                tr("Sorry, \"%1\" is already in your address book.").arg(name));
        }
    }
    else if (currentMode == EditingMode)
    {

        if (prevPerson->getName() != name)
        {
            if (!contacts.contains(name))
            {
                QMessageBox::information(this, tr("Edit Successful"),
                    tr("\"%1\" has been edited in your address book.").arg(prevPerson->getName()));
                contacts.remove(prevPerson->getName());
                AddPersonToQMap(nameLine->text(), addressText->toPlainText());
            }
            else
            {
                QMessageBox::information(this, tr("Edit Unsuccessful"),
                    tr("Sorry, \"%1\" is already in your address book.").arg(name));
            }
        }
        else if (prevPerson->getAddress() != address)
        {
            QMessageBox::information(this, tr("Edit Successful"),
                tr("\"%1\" has been edited in your address book.").arg(name));
            AddPersonToQMap(nameLine->text(), addressText->toPlainText());
        }
    }

    contactTypeCombobox->setCurrentIndex(0);
    updateInterface(NavigationMode);
}

void AddressBook::cancel()
{
    nameLine->setText(prevPerson->getName());
    addressText->setText(prevPerson->getAddress());
    updateInterface(NavigationMode);
}

void AddressBook::removeContact()
{

    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (contacts.contains(name)) {

        int button = QMessageBox::question(this,
            tr("Confirm Remove"),
            tr("Are you sure you want to remove \"%1\"?").arg(name),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {

            previous();// show previous contact because current is removed
            contacts.remove(name);

            QMessageBox::information(this, tr("Remove Successful"),
                tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }

    updateInterface(NavigationMode);
}

/*эмулировать циклически связанный список с помощью объекта класса QMap - contacts
Иллюзия того, что QMap работает как циклически связанный список.*/
void AddressBook::next()
{
    QString name = nameLine->text();
    QMap<QString, Person*>::iterator i = contacts.find(name);

    if (i != contacts.end())
        i++;

    if (i == contacts.end())
        i = contacts.begin();

    nameLine->setText(i.key());
    addressText->setText(i.value()->getAddress());
    contactTypeLabelValue->setText(i.value()->getData());
}

void AddressBook::previous()
{
    QString name = nameLine->text();
    QMap<QString, Person*>::iterator i = contacts.find(name);

    if (i == contacts.end()){
        nameLine->clear();
        addressText->clear();
        return;
    }

    if (i == contacts.begin())
        i = contacts.end();

    i--;
    nameLine->setText(i.key());
    addressText->setText(i.value()->getAddress());
}

void AddressBook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch (currentMode)
    {

    case AddingMode:

    case EditingMode:
    {
        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        addressText->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();
        break;
    }
    case NavigationMode:
    {
        if (contacts.isEmpty()) {
            nameLine->clear();
            addressText->clear();
        }

        nameLine->setReadOnly(true);
        addressText->setReadOnly(true);
        addButton->setEnabled(false);

        int number = contacts.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number >1 );
        findButton->setEnabled(number > 1);

        submitButton->hide();
        cancelButton->hide();
        break;
    }
    }

    switch (currentType) {
    case ContactType::Friends:

        break;
    case ContactType::Colleagues:

        break;
    case ContactType::Relatives:

        break;
    default:
        break;
    }
}

void AddressBook::findContact()
{
    dialog->show();

    if (dialog->exec() == QDialog::Accepted) {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName)) {
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName)->getAddress());
        } else {
            QMessageBox::information(this, tr("Contact Not Found"),
                tr("Sorry, \"%1\" is not in your address book.").arg(contactName));
            return;
        }
    }

    updateInterface(NavigationMode);
}

void AddressBook::saveToFile()
{
//    QString fileName = QFileDialog::getSaveFileName(this,
//        tr("Save Address Book"), "",
//        tr("Address Book (*.abk);;All Files (*)"));

//    if (fileName.isEmpty())
//        return;
//    else {
//        QFile file(fileName);
//        if (!file.open(QIODevice::WriteOnly)) {
//            QMessageBox::information(this, tr("Unable to open file"),
//                file.errorString());
//            return;
//        }

//        QDataStream out(&file);
//        out.setVersion(QDataStream::Qt_4_5);
//        out << contacts;
//    }
}

void AddressBook::loadFromFile()
{
//    QString fileName = QFileDialog::getOpenFileName(this,
//        tr("Open Address Book"), "",
//        tr("Address Book (*.abk);;All Files (*)"));

//    if (fileName.isEmpty())
//        return;
//    else {

//        QFile file(fileName);

//        if (!file.open(QIODevice::ReadOnly)) {
//            QMessageBox::information(this, tr("Unable to open file"),
//                file.errorString());
//            return;
//        }

//        QDataStream in(&file);
//        in.setVersion(QDataStream::Qt_4_5);
//        contacts.empty();   // очистка существующих контактов
//        in >> contacts;

//        if (contacts.isEmpty()) {
//            QMessageBox::information(this, tr("No contacts in file"),
//                tr("The file you are attempting to open contains no contacts."));
//        } else {
//            QMap<QString, Person*>::iterator i = contacts.begin();
//            nameLine->setText(i.key());
//            addressText->setText(i.value()->getAddress());
//        }
//    }

//    updateInterface(NavigationMode);

}

