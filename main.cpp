// Подключение классов
#include <QApplication>
#include "addressbook.h"

// Определение функции main()

int main(int argc, char* argv[])
{
QApplication app(argc,argv); //создаем приложение app
AddressBook *addressBook=new AddressBook;
addressBook->show();
return app.exec(); //запускаем цикл обработки событий
}
