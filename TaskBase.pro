QT += quick network sql

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS
SOURCES += \
        basereader.cpp \
        clientclass.cpp \
        main.cpp

RESOURCES += qml.qrc
QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    basereader.h \
    clientclass.h \
    header.h
TRANSLATIONS += taskbase_ru.ts
CODECFORSRC     = UTF-8
