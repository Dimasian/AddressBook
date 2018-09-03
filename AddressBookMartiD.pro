QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = AddressBookMartiD
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    addressbook.cpp \
    person.cpp \
    friend.cpp \
    colleague.cpp \
    relative.cpp \
    finddialog.cpp

HEADERS += \
    addressbook.h \
    person.h \
    friend.h \
    colleague.h \
    relative.h \
    finddialog.h


