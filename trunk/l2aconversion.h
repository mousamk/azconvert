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
    void    reloadResources();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    void setOriginalText(const QString &text);
    QString getTablesPostfix();
    bool canAddWords();


private:
    //QString ConvertHtml();
    QString convertWord(const QString& word, bool isRecursive);
    QString GetResult();
    void    separatePostfixes(const QString& word, QString& nakedWord, QString& wordPostfixes);
    void    separatePrefixes(const QString& word, QString& nakedWord, QString& wordPrefixes);
    QChar   GetSpecialChar(QChar c);
    QString GetWord(int i);
    //QString GetWord(int i, QChar delim);
    QString lookupWord(const QString& w);
    bool    IsBackVowel(QChar c);
    bool    IsCharAInWordChar(QChar c);
    bool    IsFrontVowel(QChar c);
    bool    IsNonConvertableWord(const QString& w);
    bool    IsVowel(QChar c);
    bool    isConsonant(QChar c);
    bool    isSticking(QChar c);
    bool    IsThereColonBeforeDoubleCloseBrackets(int index);   //Is used in wiki mode
    void    PreprocessText();
    void    getCharEquivalent(const QChar& ch, int columnIndex, QString& equivalent);
    
    
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
    QChar ih;
    //QChar gh;
    //QChar sh;
    //QChar ch;
    QChar Ih;
    QChar uh;
    //QChar oh;
    QChar vs;   //Virtual space

    QString vs_str;
};

#endif // L2ACONVERSION_H
