#ifndef A2LCONVERSION_H
#define A2LCONVERSION_H

#include <QObject>
#include "convertor.h"

class QProgressDialog;


class A2LConversion : public Convertor
{
public:
    A2LConversion(QObject* parent);
    QString convert(QProgressDialog*, bool wikiMode);
    //QString convert(QString text, bool wikiMode);
    //void    reloadResources();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    void setOriginalText(const QString &text);
    QString getTablesPostfix();
    bool canAddWords();

    
private:
    QString convert(QProgressDialog*, QString text);
    QString GetResult();
    QChar   GetSecondSesli(const QString&);
    void ChangeAlternativeForms();
    QString ChangePostfixes(const QString&);
    QString CheckPostfix(const QString&, const QString&, const QString&);
    QString CheckPostfix(const QString&, const QString&, const QString&, const QString&);
    int     ChooseBackOrFront(const QString&);
    bool    ContainsBackVowel(const QString&);
    QChar   ConvertSessizChar(QChar);
    QString ConvertWord(const QString&, int, bool);
    QString DescriptWord(const QString&);
    QChar   GetSpecialChar(QChar);
    QString GetWord(int);
    QString GetWordFromDictionary(const QString&);
    bool    IsCharAEndStatementChar(QChar) const;
    bool    IsCharAInWordChar(QChar) const;
    bool    IsEnd(const QString&, int);
    QString IslahEt(const QString&);
    bool    IsLatinSesli(QChar);
    bool    IsNonConvertableWord(const QString&);
    bool    IsSesli(QChar);
    //bool    IsAbsSesli(QChar);
    bool    IsSesli(const QString&, int);
    bool    IsSessiz(QChar);
    bool    IsSessiz(const QString&, int);
    bool    IsSessizYV(const QString&, int);
    QString RaiseUpFirstLetters(const QString&) const;
    int     GetHicaNumber(const QString&, int);
    
    
protected:
    /*!
     * @brief Fetches the record for a character and returns all parts in a string list.
     * @param query The query to get the fields from.
     * @param record The record to get the fields' indexes from.
     * @returns The list of fields for a character record.
     */
    QStringList getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record);

    /*!
     * @brief Gets a text and replaces some characters in it according to the 'nodiac' table.
     * @param text The text to replace its special characters.
     */
    void replaceSpecialChars(QString& text);


public:
    QString AA2AL;
    QString strResult;
};

#endif // A2LCONVERSION_H
