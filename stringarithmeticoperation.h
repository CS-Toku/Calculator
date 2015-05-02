#ifndef STRINGARITHMETICOPERATION_H
#define STRINGARITHMETICOPERATION_H

#include <iostream>
#include <gmpxx.h>
#include <QString>
#include <QRegExp>
#include <QStack>
#include <QStringList>

QString StringArithmeticOperation(QString formula);
QString parseMethod(QString formula);
void calcrateMethod(QString formula);
int symbolPriority(char ch);


#endif // STRINGARITHMETICOPERATION_H
