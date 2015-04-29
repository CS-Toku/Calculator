#-------------------------------------------------
#
# Project created by QtCreator 2015-04-22T21:11:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Calculator
TEMPLATE = app


SOURCES += main.cpp\
        calculatorwindow.cpp \
    stringarithmeticoperation.cpp

HEADERS  += calculatorwindow.h \
    stringarithmeticoperation.h

FORMS    += calculatorwindow.ui

RESOURCES +=

DISTFILES +=

macx: LIBS += -L/usr/local/Cellar/gmp/6.0.0a/lib/ -lgmpxx -lgmp
macx: INCLUDEPATH += /usr/local/Cellar/gmp/6.0.0a/include
macx: DEPENDPATH += /usr/local/Cellar/gmp/6.0.0a/include
macx: PRE_TARGETDEPS += /usr/local/Cellar/gmp/6.0.0a/lib/libgmpxx.a
