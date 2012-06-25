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
    void    openDicts();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    void setOriginalText(const QString &text);


private:
    QString CheckPostfix(const QString& w, const QString& pf, int sp);
    QString ConvertHtml();
    QChar   ConvertSessizChar(QChar c);
    QString ConvertWord(const QString& word, bool isRecursive);
    QString GetResult();
    QString ChangePostfixes(const QString& w);
    QString ChangePrefixes(const QString& w);
    QChar   GetSpecialChar(QChar c);
    QString GetSpecialWord(const QString& w);
    QString GetWord(int i);
    QString GetWord(int i, QChar delim);
    QString GetWordFromDictionary(const QString& w);
    bool    IsBackVowel(QChar c);
    bool    IsCharAInWordChar(QChar c);
    bool    IsFrontVowel(QChar c);
    bool    IsNonConvertableWord(const QString& w);
    bool    IsSesli(QChar c);
    bool    IsSessiz(QChar c);
    bool    IsSonrayaYapisan(QChar c);
    bool    IsThereColonBeforeDoubleCloseBrackets(int index);   //Is used in wiki mode
    void    PreprocessText();
    void getCharEquivalent(const QChar& ch, int columnIndex, QString& equivalent);
    
    
protected:
    //void getTablesPostfix();
    void loadChars();


public:
    QString AL2AA;
    QString strResult;

private: //chars
    QChar eh;
    QChar ih;
    QChar gh;
    QChar sh;
    QChar ch;
    QChar uh;
    QChar oh;
    QChar vs;   //Virtual space
    QChar Ih;
};

#endif // L2ACONVERSION_H
