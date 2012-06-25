#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
//#include <QFile>
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
    /*QFile file("./test.test");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "success";
        file.write("test!");
    }*/
    
    db = QSqlDatabase::addDatabase("QSQLITE", "TransliterationDb");
    QString dbFilePath = QCoreApplication::applicationDirPath() + QDir::separator() + "db.sqlite";
    db.setDatabaseName(dbFilePath);
    if (!db.open())
    {
        //qDebug() << "Error opening db: " << db.lastError().text();
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
