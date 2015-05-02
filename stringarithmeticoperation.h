#ifndef STRINGARITHMETICOPERATION_H
#define STRINGARITHMETICOPERATION_H

#include <sstream>
#include <iostream>
#include <gmpxx.h>
#include <QString>
#include <QRegExp>
#include <QStack>
#include <QStringList>

QString StringArithmeticOperation(QString formula);
QString parseMethod(QString formula);
QString calcrateMethod(QString formula);
int symbolPriority(char ch);


#endif // STRINGARITHMETICOPERATION_H
