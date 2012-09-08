#ifndef L2ACONVERSION_H
#define L2ACONVERSION_H

#include <QObject>
#include <QProgressDialog>
#include "convertor.h"


class L2AConversion : public Convertor
{
public:
    L2AConversion(QObject* parent);
    QString convert(QProgressDialog*);
    QString convert(QString text);
    void    reloadResources();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    void setOriginalText(const QString &text);
    QString getTablesPostfix();
    bool canAddWords();


private:
    QString convert(QProgressDialog*, QString text);
    QString convertWord(const QString& w);
    QString convertWordSimple(const QString& word);
    QString getResult();
    void    separatePostfixes(const QString& word, QString& nakedWord, QString& wordPostfixes);
    void    separatePrefixes(const QString& word, QString& nakedWord, QString& wordPrefixes);
    QString getSpecialChar(QChar c, int index);
    QString getWord(int i, QString source = QString());
    QString lookupWord(const QString& w);
    bool    isCharAInWordChar(QChar c);
    //bool    isBackVowel(QChar c);
    //bool    isFrontVowel(QChar c);
    bool    isNonConvertableWord(const QString& w);
    //bool    isVowel(QChar c);
    //bool    isConsonant(QChar c);
    bool    isSticking(QChar c);
    //bool    IsThereColonBeforeDoubleCloseBrackets(int index);   //Is used in wiki mode
    void    preprocessText();
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


public:
    QString strResult;


private: //chars
    QChar eh;
    //QChar ih;
    //QChar gh;
    //QChar sh;
    //QChar ch;
    //QChar Ih;
    //QChar uh;
    //QChar oh;
    QChar vs;   //Virtual space

    QString vs_str;

    QMap<int, QString> replaces;
};

#endif // L2ACONVERSION_H
