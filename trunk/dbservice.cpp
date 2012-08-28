#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDir>
#include <QCoreApplication>
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
    dbFilePath += "../../otherfiles/db.sqlite";
#else
    dbFilePath += "db.sqlite";
#endif

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


void DbService::getPrefixes(QString tablePostfix, QMap<int, QStringList> &prefixes)
{
    loadPostOrPrefix("prefix", tablePostfix, prefixes);
}


void DbService::getPostfixes(QString tablePostfix, QMap<int, QStringList> &postfixes)
{
    loadPostOrPrefix("postfix", tablePostfix, postfixes);
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

        qDebug() << "A" << postOrPrefix << "is loaded: " << id << ": " << list;
    }
}
