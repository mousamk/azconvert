#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

#include "l2cconversion.h"


L2CConversion::L2CConversion(QObject* parent)
    : Convertor(parent)
{
    reloadResources();
}


Qt::LayoutDirection L2CConversion::getSourceLayoutDirection()
{
    return Qt::LeftToRight;
}


Qt::LayoutDirection L2CConversion::getDestinationLayoutDirection()
{
    return Qt::LeftToRight;
}


QString L2CConversion::getTablesPostfix()
{
    return "_l2c";
}


bool L2CConversion::canAddWords()
{
    return false;
}


QStringList L2CConversion::getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record)
{
    QStringList tuple;
    tuple << query.value(record.indexOf("equivalent")).toString();

    return tuple;
}


void L2CConversion::replaceSpecialChars(QString &/*text*/)
{
}


QString L2CConversion::convert(QProgressDialog* /*progressDialog*/, bool /*wikiMode*/)
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
