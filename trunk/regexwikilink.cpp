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
    /*QString link1 = regexp.cap(1);
    QString link2 = regexp.cap(2);
    QString link = link2.isEmpty() ? link1 : link2;
    convertor->setOriginalText(link);
    QString equivalent = convertor->convert(NULL, false);
    QString fullEqual = "[[" + link1;
    if (link1 != equivalent)
        fullEqual += "|" + equivalent;
    fullEqual += "]]";

    return fullEqual;*/

    //<<<Temporary:
    QString link1 = regexp.cap(1);
    QString link2 = regexp.cap(2);
    convertor->setOriginalText(link1);
    QString link1Eq = convertor->convert(NULL, false);
    QString link2Eq = "";
    if (!link2.isEmpty())
    {
        convertor->setOriginalText(link2);
        link2Eq = convertor->convert(NULL, false);
    }

    QString equivalent = "[[Wp/azb/";
    if (!link2.isEmpty())
    {
        equivalent += link1Eq + "|" + link2Eq;
    }
    else
    {
        equivalent += link1Eq + "|" + link1Eq;
    }
    equivalent += "]]";

    return equivalent;
    //>>>
}
