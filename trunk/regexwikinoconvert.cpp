#include <QDebug>
#include <QStringList>
#include "regexwikinoconvert.h"
#include "config.h"


RegexWikiNoConvert::RegexWikiNoConvert(QString &source)
    : Regex(source)
{
    QString pattern = "(?:\\`\\{\\`\\{\\s*" + QString(WIKI_NO_CONVERT_TAG) + "\\s*\\|(?:[^\\`]|\\`\\`)*\\`\\}\\`\\})";
    regexp.setPattern(pattern);
}


QString RegexWikiNoConvert::getMatchEquivalent()
{
    qDebug() << "NOCONVERT template Found:" << regexp.capturedTexts();
    //No conversion is needed:
    return regexp.cap();
}
