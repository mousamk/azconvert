/*!
 * @file convertor.h
 * @brief This files contains declaration of Convertor class.
 *
 * @author Mousa Moradi
 */

#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <QObject>
#include <QHash>
#include <QMap>
#include <QStringList>


class QProgressDialog;

template <class Key, class T>
class QHash;
class QSqlQuery;
class QSqlRecord;

/*!
 * @class Convertor
 * @brief This class is the base class of convertor classes, specifies their interface,
 *  and implements common features.
 */
class Convertor : public QObject
{
    Q_OBJECT
    
    
public:
    /*!
     * @brief Class constructor
     * @param parent Parent for the new object to be created
     */
    Convertor(QObject* parent);
    
    /*!
     * @brief Class destructor
     */
    ~Convertor();
    
    /*!
     * @brief Converts the previously set original text and returns the result.
     * @param progressDialog The progressDialog to update it while converting
     * @return The converted result
     */
    //TODO: Eliminate the parameter and setup a better synchronization system.
    virtual QString convert(QProgressDialog* progressDialog) = 0;
    
    /*!
     * @brief Reloads the dictionaries.
     */
    //TODO: A better name or mechanism.
    //virtual void openDicts() = 0;
    
    /*!
     * @brief Sets the original text to be used later in converting.
     * @param text The orginial text to be converted later
     */
    virtual void setOriginalText(const QString& text) {strSource = text;}
    
    /*!
     * @brief Returns layout direction of the source script to be used in window.
     * @return The layout direction for the source script
     */
    virtual Qt::LayoutDirection getSourceLayoutDirection() = 0;
    
    /*!
     * @brief Returns layout direction of the destination script to be used in window.
     * @return The layout direction for the destination script
     */
    virtual Qt::LayoutDirection getDestinationLayoutDirection() = 0;
    
    
protected:
    /*!
     * @brief Loads character table used for base transliteration
     */
    void loadChars();

    /*!
     * @brief Loads words table used in transliteration
     */
    void loadWords();

    /*!
     * @brief Loads prefixes table used in transliteration
     */
    void loadPrefixes();

    /*!
     * @brief Loads postfixes table used in transliteration
     */
    void loadPostfixes();
    
    /*!
     * @brief Gets the convertor's postfix for database tables
     * @returns The postfix of the convertor in db tables
     */
    virtual QString getTablesPostfix() = 0;

    /*!
     * @brief Fetches the record for a character and returns all parts in a string list.
     * @param query The query to get the fields from.
     * @param record The record to get the fields' indexes from.
     * @returns The list of fields for a character record.
     */
    virtual QStringList getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record) = 0;
    
    
protected:
    /// @brief The original source text to be converted
    QString strSource;
    
    /// @brief The transliteration table of characeters
    QHash<QChar, QStringList> chars;
    
    /// @brief Table of words and their equivalents used for conversion
    QHash<QString, QString> words;

    /// @brief Table of prefixes and their related fields
    QMap<int, QStringList> prefixes;

    /// @brief Table of postfixes and their related fields
    QMap<int, QStringList> postfixes;
};

#endif // CONVERTOR_H
