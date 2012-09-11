#include <QDebug>
#include <QStringList>
#include "regexwikinowiki.h"
#include "convertor.h"


RegexWikiNoWiki::RegexWikiNoWiki(QString &source, Convertor* convertor)
    : Regex(source), convertor(convertor)
{
    QString pattern = "\\<nowiki\\>(.*)\\<\\/nowiki\\>";
    regexp.setPattern(pattern);
}


RegexWikiNoWiki::~RegexWikiNoWiki()
{
    delete convertor;
}


QString RegexWikiNoWiki::getMatchEquivalent()
{
    qDebug() << "NOWIKI Found:" << regexp.capturedTexts();

    //Get inner contents of nowiki tag and convert it:
    convertor->setOriginalText(regexp.cap(1));
    QString inner = convertor->convert(NULL, false);
    QString equivalent = "<nowiki>" + inner + "</nowiki>";

    return equivalent;
}
