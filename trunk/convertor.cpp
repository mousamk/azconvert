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
    chars.clear();

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


void Convertor::loadSpecialChars()
{
    specialChars.clear();
    DbService::getInstance()->getSpecialChars(getTablesPostfix(), specialChars);
}


void Convertor::loadWords()
{
    words.clear();
    DbService::getInstance()->getWords(getTablesPostfix(), words);
}


void Convertor::loadSolidWords()
{
    solidWords.clear();
    DbService::getInstance()->getSolidWords(getTablesPostfix(), solidWords);
}


void Convertor::loadPrefixes()
{
    prefixes.clear();
    DbService::getInstance()->getPrefixes(getTablesPostfix(), prefixes);
}


void Convertor::loadPostfixes()
{
    postfixes.clear();
    DbService::getInstance()->getPostfixes(getTablesPostfix(), postfixes);
}
