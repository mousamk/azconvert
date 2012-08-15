#ifndef A2LCONVERSION_H
#define A2LCONVERSION_H

#include <QObject>
#include <QProgressDialog>
#include "convertor.h"


class A2LConversion : public Convertor
{
public:
    A2LConversion(QObject* parent);
    QString convert(QProgressDialog*);
    //void    openDicts();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    void setOriginalText(const QString &text);

    
private:
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
    bool    IsCharAEndStatementChar(QChar);
    bool    IsCharAInWordChar(QChar);
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
    void    RaiseUpFirstLetters();
    int     GetHicaNumber(const QString&, int);
    
    
protected:
    QString getTablesPostfix();

    /*!
     * @brief Fetches the record for a character and returns all parts in a string list.
     * @param query The query to get the fields from.
     * @param record The record to get the fields' indexes from.
     * @returns The list of fields for a character record.
     */
    QStringList getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record);


public:
    QString AA2AL;
    QString strResult;
};

#endif // A2LCONVERSION_H
