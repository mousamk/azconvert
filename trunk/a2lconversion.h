#ifndef A2LCONVERSION_H
#define A2LCONVERSION_H

#include <QObject>
#include <QProgressDialog>

class A2LConversion : public QObject
{
public:
    A2LConversion();


public:
    QString Convert(QProgressDialog*);
    QString GetResult();
    QChar   GetSecondSesli(const QString&);
    void    OpenDicts();
    void    SetOriginalText(const QString&);

private:
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


public:
    QString AA2AL;
    QString strResult;
    QString strSource;
};

#endif // A2LCONVERSION_H
