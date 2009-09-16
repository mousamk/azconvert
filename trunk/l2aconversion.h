#ifndef L2ACONVERSION_H
#define L2ACONVERSION_H


#include <QString>
#include <QObject>
#include <QProgressDialog>


class L2AConversion : public QObject
{
    //Q_DECLARE_TR_FUNCTIONS(L2AConversion);

public:
    L2AConversion();
    QString ChangePostfixes(const QString& w);
    QString ChangePrefixes(const QString& w);
    QString CheckPostfix(const QString& w, const QString& pf, int sp);
    QString Convert(QProgressDialog*);
    QString ConvertHtml();
    QChar   ConvertSessizChar(QChar c);
    QString ConvertWord(const QString& word, bool isRecursive);
    QString GetResult();
    void    OpenDicts();
    void    SetOriginalText(const QString& str);


private:
    QChar   GetSpecialChar(QChar c);
    QString GetSpecialWord(const QString& w);
    QString GetWord(int i);
    QString GetWordFromDictionary(const QString& w);
    bool    IsBackVowel(QChar c);
    bool    IsCharAInWordChar(QChar c);
    bool    IsFrontVowel(QChar c);
    bool    IsNonConvertableWord(const QString& w);
    bool    IsSesli(QChar c);
    bool    IsSessiz(QChar c);
    bool    IsSonrayaYapisan(QChar c);
    void    PreprocessText();


public:
    QString AL2AA;
    QString strResult;
    QString strSource;

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
