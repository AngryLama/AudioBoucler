#ifndef CONVERSION_H
#define CONVERSION_H
#include <iostream>
#include <QStringList>
#include <QKeySequence>

QString charToQString(const char* chaine);
uint QStringToKey(QString const & str);
QString msToQString(qint64 temps);
qint64 QStringToMs(QString temps);

#endif // CONVERSION_H
