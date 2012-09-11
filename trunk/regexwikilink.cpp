#include <QDebug>
#include <QStringList>
#include "regexwikilink.h"
#include "convertor.h"


RegexWikiLink::RegexWikiLink(QString &source, Convertor* convertor)
    : Regex(source), convertor(convertor)
{
    QString pattern = "\\[\\[([^\\|\\]\\:]+)(?:\\|([^\\]]+))?\\]\\]";
    regexp.setPattern(pattern);
}


RegexWikiLink::~RegexWikiLink()
{
    delete convertor;
}


QString RegexWikiLink::getMatchEquivalent()
{
    qDebug() << "LINK found:" << regexp.capturedTexts();
    //QString match = regexp.cap();
    QString link1 = regexp.cap(1);
    QString link2 = regexp.cap(2);
    QString link = link2.isEmpty() ? link1 : link2;
    convertor->setOriginalText(link);
    QString equivalent = convertor->convert(NULL, false);
    QString fullEqual = "[[" + link1;
    if (link1 != equivalent)
        fullEqual += "|" + equivalent;
    fullEqual += "]]";

    return fullEqual;
}
