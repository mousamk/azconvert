#include <QDebug>
#include <QStringList>
#include "regexwikiinterwiki.h"


RegexWikiInterwiki::RegexWikiInterwiki(QString &source, Convertor* convertor)
    : Regex(source, convertor)
{
    QString pattern = "\\[\\[[a-zA-Z\\-]+\\:[^\\]\\|]*\\]\\]";      //TODO: Check the new pipe added
    regexp.setPattern(pattern);
}


QString RegexWikiInterwiki::getMatchEquivalent()
{
    qDebug() << "Interwiki is found: " << regexp.capturedTexts();
    //No conversion is needed:
    return regexp.cap();
}
