#include <QVariant>
#include "convertor.h"
#include "dbservice.h"


Convertor::Convertor(QObject *parent)
    : QObject(parent)
{
}


Convertor::~Convertor()
{
}


void Convertor::loadChars()
{
    QSqlRecord record;
    QSqlQuery query;
    DbService::getInstance()->getCharacters(getTablesPostfix(), record, query);
    while(query.next())
    {
        QChar character = query.value(record.indexOf("source")).toString().at(0);
        QStringList tuple = getCharacterTuple(query, record);

        chars.insert(character, tuple);
    }
}


void Convertor::loadWords()
{
    DbService::getInstance()->getWords(getTablesPostfix(), words);
}
