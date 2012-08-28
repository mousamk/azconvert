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


template <class Key, class T>
class QHash;


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
    void getWords(QString tablePostfix, QHash<QString,QString>& words);

    /*!
     * @brief Loads prefixes for the table given by @p tablePostfix and returns
     *        them in the @p prefixes parameter.
     * @param tablePostfix Postfix of the table to load prefixes from it
     * @param prefixes The reference where the prefixes loaded will be saved in
     */
    void getPrefixes(QString tablePostfix, QMap<int,QStringList>& prefixes);

    /*!
     * @brief Loads postfixes for the table given by @p tablePostfix and returns
     *        them in the @p postfixes parameter.
     * @param tablePostfix Postfix of the table to load postfixes from it
     * @param postfixes The reference where the postfixes loaded will be saved in
     */
    void getPostfixes(QString tablePostfix, QMap<int,QStringList>& postfixes);
    
    
private:
    explicit DbService(QObject *parent);
    bool loadDb();
    void loadPostOrPrefix(QString postOrPrefix, QString tablePostfix, QMap<int,QStringList>& postOrPrefixes);
    
    
private:
    static DbService* instance;
    QSqlDatabase db;
};

#endif // DBSERVICE_H
