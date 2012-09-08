#include <QDebug>
#include <QStringList>
#include "regexwikilink.h"
#include "convertor.h"


RegexWikiLink::RegexWikiLink(QString &source, Convertor* convertor)
    : Regex(source, convertor)
{
    QString pattern = "\\[\\[([^\\|\\]\\:]+)(?:\\|([^\\]]+))?\\]\\]";
    regexp.setPattern(pattern);
}


QString RegexWikiLink::getMatchEquivalent()
{
    qDebug() << "LINK found:" << regexp.capturedTexts();
    //QString match = regexp.cap();
    QString link1 = regexp.cap(1);
    QString link2 = regexp.cap(2);
    QString link = link2.isEmpty() ? link1 : link2;
    QString equivalent = convertor->convert(link);
    QString fullEqual = "[[" + link1 + "|" + equivalent + "]]";

    return fullEqual;
}
