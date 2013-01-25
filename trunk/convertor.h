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
#include <QList>

#include "specialcharacterrecord.h"
#include "charreplacerecord.h"


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
     * @param wikiMode Indicates whether the text be treated as wiki format and
     *        the required consideration be done or not
     * @return The converted result
     */
    virtual QString convert(QProgressDialog* progressDialog, bool wikiMode) = 0;

    /* !
     * @brief Converts a text without considering progress dialog.
     * @param text The text to be converted.
     * @param wikiMode Indicates whether the text be treated as wiki format and
     *        the required consideration be done or not
     * @return The converted result
     */
    //virtual QString convert(QString text, bool wikiMode) = 0;
    
    /*!
     * @brief Reloads the database resource.
     * @param force Indicates whether the reloading must be done ignoring conditions or not
     */
    void reloadResources(bool force = false);
    
    /*!
     * @brief Sets the original text to be used later in converting.
     * @param text The orginial text to be converted later
     */
    void setOriginalText(const QString& text);

    /*!
     * @brief Gets the converted result
     * @return Returns the converted result
     */
    QString getConvertedResult();
    
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

    /*!
     * @brief Returns the words collection.
     * @return The words collection
     */
    QHash<QString,QString>& getWords();

    /*!
     * @brief Gets the replace chars list.
     * @return The replace chars list.
     */
    QMap<int, CharReplaceRecord>& getReplaceChars();

    /*!
     * @brief Gets the convertor's postfix for database tables
     * @returns The postfix of the convertor in db tables
     */
    virtual QString getTablesPostfix() = 0;

    /*!
     * @brief Returns whether words can be added to this conversion mode or not.
     * @return Whether words can be added to this conversion or not.
     */
    virtual bool canAddWords() = 0;
    
    
protected:
    //! @brief Loads character table used for base transliteration
    void loadChars();

    //! @brief Loads special character conversion table for transliteration
    void loadSpecialChars();

    //! @brief Loads words table used in transliteration
    void loadWords();

    //! @brief Loads solid words table
    void loadSolidWords();

    //! @brief Loads prefixes table used in transliteration
    void loadPrefixes();

    //! @brief Loads postfixes table used in transliteration
    void loadPostfixes();

    //! @brief Loads replaced character records
    void loadReplaceChars();

    /*!
     * @brief Fetches the record for a character and returns all parts in a string list.
     * @param query The query to get the fields from.
     * @param record The record to get the fields' indexes from.
     * @returns The list of fields for a character record.
     */
    virtual QStringList getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record) = 0;

    /*!
     * @brief Gets a text and replaces some characters in it according to the 'nodiac' table.
     * @param text The text to replace its special characters.
     */
    virtual void replaceSpecialChars(QString& text) = 0;
    
    
protected:
    //! @brief The original source text to be converted
    QString strSource;

    //! @brief The converted text
    QString strResult;

    //! @brief The transliteration table of characeters
    static QHash<QChar, QStringList> chars;

    //! @brief The transliteration table of special characters
    static QMap<int, SpecialCharacterRecord> specialChars;

    //! @brief Table of words and their equivalents used for conversion
    static QHash<QString, QString> words;

    //! @brief List of non-convertible words
    static QList<QString> solidWords;

    //! @brief Table of prefixes and their related fields
    static QMap<int, QStringList> prefixes;

    //! @brief Table of postfixes and their related fields
    static QMap<int, QStringList> postfixes;

    //! @brief Table of character replacing records
    static QMap<int, CharReplaceRecord> replaceChars;

    //! @brief The loaded mode's table postfix will be saved in this when db data are loaded:
    static QString loadedMode;
};

#endif // CONVERTOR_H
