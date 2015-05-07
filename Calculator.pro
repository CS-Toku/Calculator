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

DISTFILES += \
    Calc.icns \
    Calc.ico \
    Calc.rc


win32: RC_FILE = Calc.rc

macx: LIBS += -L/usr/local/Cellar/gmp/6.0.0a/lib/ -lgmp -lgmpxx
macx: INCLUDEPATH += /usr/local/Cellar/gmp/6.0.0a/include
macx: DEPENDPATH += /usr/local/Cellar/gmp/6.0.0a/include
macx: PRE_TARGETDEPS += /usr/local/Cellar/gmp/6.0.0a/lib/libgmp.a
macx: PRE_TARGETDEPS += /usr/local/Cellar/gmp/6.0.0a/lib/libgmpxx.a
macx: ICON = Calc.icns

unix:!macx: LIBS += -L/usr/local/lib -L/usr/lib -lgmp -lgmpxx
unix:!macx: INCLUDEPATH += /usr/local/include
unix:!macx: DEPENDPATH += /usr/local/include
unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libgmp.a
unix:!macx: PRE_TARGETDEPS += /usr/local/lib/libgmpxx.a
