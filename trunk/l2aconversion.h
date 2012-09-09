#ifndef L2ACONVERSION_H
#define L2ACONVERSION_H

#include <QObject>
#include <QProgressDialog>
#include "convertor.h"


class L2AConversion : public Convertor
{
public:
    L2AConversion(QObject* parent);
    QString convert(QProgressDialog*, bool wikiMode);
    QString convert(QString text, bool wikiMode);
    //void    reloadResources();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    void setOriginalText(const QString &text);
    QString getTablesPostfix();
    bool canAddWords();


private:
    QString convert(QProgressDialog*, QString text);

    /*!
     * @brief Converts the given word and returns the result
     * @param w The word to be converted
     * @param part Indicates whether it's a (right) part of another word, or
     *        is a standalone word.
     * @return The converted result
     */
    QString convertWord(const QString& w, bool part);

    /*!
     * @brief Converts a word with basic transliteration algorithm.
     * @param word The word to be converted
     * @return The converted result
     */
    QString convertWordSimple(const QString& word);
    void    separatePostfixes(const QString& word, bool part, QString& nakedWord, QString& wordPostfixes);
    void    separatePrefixes(const QString& word, QString& nakedWord, QString& wordPrefixes);
    QString getSpecialChar(QChar c, int index);
    QString getWord(int i, QString source = QString());
    QString lookupWord(const QString& w);
    bool    isCharAInWordChar(QChar c);
    bool    isNonConvertableWord(const QString& w);
    bool    isSticking(QChar c);
    void    preprocessText(bool wikiMode);
    void    postprocessText();
    QString preprocessWord(QString word);
    void    getCharEquivalent(const QChar& ch, int columnIndex, QString& equivalent);
    int     getCharacterCount(QChar character, int position);
    
    
protected:
    /*!
     * @brief Fetches the record for a character and returns all parts in a string list.
     * @param query The query to get the fields from.
     * @param record The record to get the fields' indexes from.
     * @returns The list of fields for a character record.
     */
    QStringList getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record);


private:
    //! @brief The conversion result
    //QString strResult;

    //! @brief The turned e character
    QChar eh;

    //! @brief The virtual space character
    QChar vs;

    //! @brief The virtual space string
    QString vs_str;

    //! @brief Map of the placeholders to return them back
    QMap<int, QString> replaces;
};

#endif // L2ACONVERSION_H
