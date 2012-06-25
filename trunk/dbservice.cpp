#include <QSqlError>
#include <QDebug>
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
    db.setDatabaseName("db.sqlite");
    if (!db.open())
    {
        qDebug() << "Error opening db: " << db.lastError().text();
        return false;
    }
    
    return true;
}
