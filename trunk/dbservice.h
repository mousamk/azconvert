/*!
 * @file dbservice.h
 * @brief This files contains declaration of DbService class.
 * @author Mousa Moradi
 */

#ifndef DBSERVICE_H
#define DBSERVICE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>


/*!
 * @class DbService
 * @brief The DbService class used to provide database service for other classes.
 */
class DbService : public QObject
{
    Q_OBJECT
    
    
public:
    static bool createInstance(QObject* parent);
    static DbService* getInstance();
    void getCharacters(QString tablePostfix, QSqlRecord& record, QSqlQuery& query);
    
    
private:
    explicit DbService(QObject *parent);
    bool loadDb();
    
    
private:
    static DbService* instance;
    QSqlDatabase db;
};

#endif // DBSERVICE_H
