#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QCoreApplication>
#include <QVariant>

#include "dbservice.h"


//Allocate memory for static member variable:
DbService* DbService::instance = NULL;


DbService::DbService(QObject *parent) :
    QObject(parent)
{
}


bool DbService::createInstance(QObject *parent)
{
    if (NULL == instance)
    {
        instance = new DbService(parent);
        return instance->loadDb();
    }

    return true;
}


DbService* DbService::getInstance()
{
    return instance;
}


bool DbService::loadDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE", "TransliterationDb");
    QString dbFilePath = QCoreApplication::applicationDirPath() + QDir::separator();

#ifdef DEBUG_BUILD
    dbFilePath += "../otherfiles/";
    //qDebug() << "HII";
#endif
	dbFilePath += "db.sqlite";

    db.setDatabaseName(dbFilePath);
    if (!db.open())
    {
        qDebug() << "Error opening db: " << db.lastError().text();
        qDebug() << "db location: " << dbFilePath;
        return false;
    }
    
    return true;
}


void DbService::getCharacters(QString tablePostfix, QSqlRecord& record, QSqlQuery& query)
{
    QString queryStr = "SELECT * FROM characters" + tablePostfix + ";"; 
    query = QSqlQuery(queryStr, db);
    record = query.record();
}


void DbService::getWords(QString tablePostfix, QHash<QString, QString> &words)
{
    //qDebug() << "going to load words";
    QString queryStr = "SELECT * FROM words" + tablePostfix + ";";
    QSqlQuery query(queryStr, db);
    QSqlRecord record = query.record();

    while(query.next())
    {
        words.insert(query.value(record.indexOf("source")).toString(), query.value(record.indexOf("equivalent")).toString());
    }
}


void DbService::getSolidWords(QString tablePostfix, QList<QString> &solidWords)
{
    QString queryStr = "SELECT * FROM solid_words" + tablePostfix + ";";
    QSqlQuery query(queryStr, db);
    QSqlRecord record = query.record();

    QString word;
    while(query.next())
    {
        word = query.value(record.indexOf("source")).toString();
        solidWords.append(word);

        //qDebug() << "A non-convertible word is loaded: " << word;
    }
}


void DbService::getSpecialChars(QString tablePostfix, QMap<int, SpecialCharacterRecord> &specialChars)
{
    QString queryStr = "SELECT * FROM special_characters" + tablePostfix + ";";
    QSqlQuery query(queryStr, db);
    QSqlRecord record = query.record();

    QString source;
    QString equivalent;
    int position;
    int id;
    while(query.next())
    {
        id = query.value(record.indexOf("id")).toInt();
        source = query.value(record.indexOf("source")).toString();
        equivalent = query.value(record.indexOf("equivalent")).toString();
        position = query.value(record.indexOf("position")).toInt();

        SpecialCharacterRecord characterRecord(source, equivalent, SpecialCharacterSituation(position));
        specialChars.insert(id, characterRecord);

        //qDebug() << "A special character is loaded: " << id << ":" << source << "," << equivalent << "," << position;
    }
}


void DbService::getPrefixes(QString tablePostfix, QMap<int, QStringList> &prefixes)
{
    loadPostOrPrefix("prefix", tablePostfix, prefixes);
}


void DbService::getPostfixes(QString tablePostfix, QMap<int, QStringList> &postfixes)
{
    loadPostOrPrefix("postfix", tablePostfix, postfixes);
}


void DbService::getReplaceChars(QString tablePostfix, QMap<int, CharReplaceRecord> &replaceChars)
{
    QString queryStr = "SELECT * FROM nodiac_" + QString(tablePostfix.at(tablePostfix.length()-1)) + ";";
    QSqlQuery query(queryStr, db);
    QSqlRecord record = query.record();

    int id, enabled;
    QString source, equivalent;
    while(query.next())
    {
        id = query.value(record.indexOf("id")).toInt();
        source = query.value(record.indexOf("source")).toString();
        equivalent = query.value(record.indexOf("equivalent")).toString();
        enabled = query.value(record.indexOf("enabled")).toInt();

        CharReplaceRecord replaceRecord(id, source, equivalent, bool(enabled));
        replaceChars.insert(id, replaceRecord);
    }
}


void DbService::loadPostOrPrefix(QString postOrPrefix, QString tablePostfix, QMap<int, QStringList> &postOrPrefixes)
{
    QString queryStr = "SELECT * FROM " + postOrPrefix + tablePostfix + ";";
    QSqlQuery query(queryStr, db);
    QSqlRecord record = query.record();

    int id;
    //QString source;
    QStringList list;
    while(query.next())
    {
        list.clear();

        id = query.value(record.indexOf("id")).toInt();
        //source = query.value(record.indexOf("source")).toString();
        list << query.value(record.indexOf("source")).toString()
             << query.value(record.indexOf("equivalent")).toString()
             << query.value(record.indexOf("type")).toString()
             << query.value(record.indexOf("dict")).toString();
        postOrPrefixes.insert(id, list);

        //qDebug() << "A" << postOrPrefix << "is loaded: " << id << ": " << list;
    }
}


bool DbService::updateReplaceChar(QString tablePostfix, int id, bool enabled)
{
    QString queryStr = "UPDATE nodiac_" + QString(tablePostfix.at(tablePostfix.length()-1)) + " "
            "SET enabled=%1 "
            "WHERE id=%2;";
    queryStr = queryStr.arg(int(enabled)).arg(id);
    QSqlQuery query(db);
    query.prepare(queryStr);

    //Execute query:
    bool res = query.exec();
    if(!res)
        qDebug() << "Error happened: " << query.lastError().text();

    return query.exec();
}


bool DbService::addWord(QString tablePostfix, QString word, QString equal)
{
    int id = getFreeId("words" + tablePostfix);
    bool res = false;
    if (-1 != id)
    {
        QString queryStr = "INSERT INTO words" + tablePostfix + " "
                "(id, source, equivalent, user_added, user_edited, submitted) "
                "VALUES(%1, '%2', '%3', 1, 0, 0);";
        queryStr = queryStr.arg(id).arg(word).arg(equal);
        QSqlQuery query(db);
        query.prepare(queryStr);

        //qDebug() << "query: " << queryStr;

        //Execute query:
        res = query.exec();
        if(!res)
            qDebug() << "An error happened: " << query.lastError().text();
        return res;
    }

    return res;
}


bool DbService::updateWord(QString tablePostfix, QString word, QString equal)
{
    QString queryStr = "UPDATE words" + tablePostfix + " "
            "SET equivalent='%1', "
            "user_edited=1, "
            "submitted=0 "
            "WHERE source='%2';";
    queryStr = queryStr.arg(equal, word);
    QSqlQuery query(db);
    query.prepare(queryStr);

    //qDebug() << "query: " << queryStr;

    //Execute query:
    bool res = query.exec();
    if(!res)
        qDebug() << "Error happened: " << query.lastError().text();

    return query.exec();
}


int DbService::getFreeId(QString table)
{
    QString queryStr = "SELECT id FROM " + table + " ORDER BY id DESC LIMIT 1;";
    //qDebug() << "query: " << queryStr;
    QSqlQuery query(queryStr, db);
    QSqlRecord record = query.record();

    int res = 0;
    if(query.next())
        res = query.value(record.indexOf("id")).toInt();

    return res > 0 ? res+1 : -1;
}
