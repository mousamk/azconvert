#ifndef C2LCONVERSION_H
#define C2LCONVERSION_H

#include <QObject>
#include <QString>

class C2LConversion : public QObject
{
public:
    C2LConversion();
    QString Convert(QString);
};

#endif // C2LCONVERSION_H
