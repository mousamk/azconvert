#ifndef C2LCONVERSION_H
#define C2LCONVERSION_H

#include <QObject>
#include <QString>
#include <QProgressDialog>
#include "convertor.h"


class C2LConversion : public Convertor
{
public:
    C2LConversion(QObject* parent);
    QString convert(QProgressDialog* progressDialog);
    void openDicts() {}
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    
    
protected:
    //void getTablesPostfix();
    void loadChars();
};

#endif // C2LCONVERSION_H
