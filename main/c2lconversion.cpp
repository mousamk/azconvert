#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "c2lconversion.h"


C2LConversion::C2LConversion(QObject* parent)
    : Convertor(parent)
{
    reloadResources();
}


/*void C2LConversion::reloadResources()
{
    loadChars();
    //loadWords();      //Not needed in this direction.
    //loadSolidWords();
    //loadPrefixes();
    //loadPostfixes();
    //loadSpecialChars();
}*/


Qt::LayoutDirection C2LConversion::getSourceLayoutDirection()
{
    return Qt::LeftToRight;
}


Qt::LayoutDirection C2LConversion::getDestinationLayoutDirection()
{
    return Qt::LeftToRight;
}


QString C2LConversion::getTablesPostfix()
{
    return "_c2l";
}


bool C2LConversion::canAddWords()
{
    return false;
}


QStringList C2LConversion::getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record)
{
    QStringList tuple;
    tuple << query.value(record.indexOf("equivalent")).toString();

    return tuple;
}


void C2LConversion::replaceSpecialChars(QString &/*text*/)
{
}


/*QString C2LConversion::convert(QString text, bool / *wikiMode* /)
{
    QString str = text;
    ...

    return str;
}*/


QString C2LConversion::convert(QProgressDialog* /*progressDialog*/, bool /*wikiMode*/)
{
    QString str = "";
    for(int i=0; i<strSource.size(); i++)
    {
        QChar ch = strSource[i];
        if (chars.contains(ch))
            str += chars[ch].at(0);
        else
            str += ch;
    }

    strResult = str;
    return strResult;
}

