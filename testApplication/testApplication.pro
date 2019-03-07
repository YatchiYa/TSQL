
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testApplication
TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += c++11

SOURCES += \
        main.cpp \
    dataC/mainwindow.cpp \
    dataC/utilities.cpp \
    dataC/grammar.cpp \
    dataC/ast.cpp \
    dataC/record.cpp \
    dataC/resultrecord.cpp \
    dataC/allrecords.cpp \
    dataC/recordmanager.cpp \
    dataC/grammartest.cpp

HEADERS += \
        mainwindow.h \
    dataH/mainwindow.h \
    includes.h \
    dataH/utilties.h \
    dataH/grammar.h \
    dataH/ast.h \
    dataH/record.h \
    dataH/resultrecord.h \
    dataH/allrecords.h \
    dataH/recordmanager.h \
    dataH/grammartest.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/'../../../../../../../../Program Files/boost_1_69_0/boost_1_69_0'
DEPENDPATH += $$PWD/'../../../../../../../../Program Files/boost_1_69_0/boost_1_69_0'

DISTFILES += \
    DB/DB.json \
    DB/Schema DataBase.sql \
    DB/DB.csv \
    DB/DB.txt
