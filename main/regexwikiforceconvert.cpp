#include <QDebug>
#include <QStringList>
#include "regexwikiforceconvert.h"
#include "config.h"


RegexWikiForceConvert::RegexWikiForceConvert(QString &source)
    : Regex(source)
{
    QString pattern = "(?:\\`\\{\\`\\{\\s*" +
            QString(WIKI_FORCE_CONVERT_TAG) +
            "\\s*\\|(?:[^\\`\\|]|\\`\\`)*"
            "\\|((?:[^\\`]|\\`\\`)*)"
            "\\`\\}\\`\\})";
    regexp.setPattern(pattern);
}


QString RegexWikiForceConvert::getMatchEquivalent()
{
    qDebug() << "FORCECONVERT template Found:" << regexp.capturedTexts();
    //Return the captured text, which is the second parameter of template:
    return regexp.cap(1);
}
