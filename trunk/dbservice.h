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

#include "specialcharacterrecord.h"
#include "charreplacerecord.h"


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
     * @brief Loads the non-convertible words from db and stores it in the given
     *        @p solidWords parameter.
     * @param tablePostfix Postfix of the table to load non-convertible words from.
     * @param solidWords The reference where the non-convertible words will be saved in.
     */
    void getSolidWords(QString tablePostfix, QList<QString>& solidWords);

    /*!
     * @brief Loads special character conversion table for the table with the
     *        giver @tablePostfix and returns them in the @p specialChars parameter.
     * @param tablePostfix Postfix of the table to load special characters from.
     * @param specialChars The reference where the special characters will be saved in.
     */
    void getSpecialChars(QString tablePostfix, QMap<int,SpecialCharacterRecord>& specialChars);

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

    /*!
     * @brief Loads characters for being replaced after transliteration
     * @param tablePostfix Postfix of the table to load postfixes from it
     * @param replaceChars The reference where the replace characters will be saved in
     */
    void getReplaceChars(QString tablePostfix, QMap<int, CharReplaceRecord>& replaceChars);

    /*!
     * @brief Updates enabled status of a replace character in database.
     * @param tablePostfix Postfix of the table to update this record on it.
     * @param id Id of the record of the replace character.
     * @param enabled Specifies whether this replacing is enabled or not.
     * @return Returns whether it's been successfully updated or not.
     */
    bool updateReplaceChar(QString tablePostfix, int id, bool enabled);

    /*!
     * @brief Adds a word to database.
     * @param tablePostfix Postfix of the table to add word to it.
     * @param word The word to be added.
     * @param equal Equivalent of the word to be added.
     * @return Returns whether it's been successfully added or not.
     */
    bool addWord(QString tablePostfix, QString word, QString equal);

    /*!
     * @brief Updates a word's equivalent in database.
     * @param tablePostfix Postfix of the table to update word in it.
     * @param word The word, it's equivalent to be updated.
     * @param equal Equivalent of the word to be updated.
     * @return Returns whether it's been successfully updated or not.
     */
    bool updateWord(QString tablePostfix, QString word, QString equal);
    
    
private:
    explicit DbService(QObject *parent);
    bool loadDb();
    void loadPostOrPrefix(QString postOrPrefix, QString tablePostfix, QMap<int,QStringList>& postOrPrefixes);
    int  getFreeId(QString table);
    
    
private:
    static DbService* instance;
    QSqlDatabase db;
};

#endif // DBSERVICE_H
