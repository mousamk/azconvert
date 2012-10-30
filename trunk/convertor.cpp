#include <QVariant>
#include <QDebug>
#include "convertor.h"
#include "dbservice.h"


//Allocate memory for static member variables:
QHash<QChar, QStringList> Convertor::chars;
QMap<int, SpecialCharacterRecord> Convertor::specialChars;
QHash<QString, QString> Convertor::words;
QList<QString> Convertor::solidWords;
QMap<int, QStringList> Convertor::prefixes;
QMap<int, QStringList> Convertor::postfixes;
QString Convertor::loadedMode;


Convertor::Convertor(QObject *parent)
    : QObject(parent)
{
}


Convertor::~Convertor()
{
}


void Convertor::reloadResources(bool force)
{
    QString postfix = getTablesPostfix();
    if (force || loadedMode != postfix)
    {
        loadChars();
        loadWords();
        loadSolidWords();
        loadPrefixes();
        loadPostfixes();
        loadSpecialChars();

        loadedMode = postfix;

        qDebug() << "Loaded for this mode:" << postfix;
    }
}


void Convertor::setOriginalText(const QString &text)
{
    strSource = text;
    strResult = "";
}


QString Convertor::getConvertedResult()
{
    return strResult;
}


QHash<QString,QString>& Convertor::getWords()
{
     return words;
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
