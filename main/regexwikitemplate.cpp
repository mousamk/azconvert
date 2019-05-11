#include <QDebug>
#include <QStringList>
#include "regexwikitemplate.h"


RegexWikiTemplate::RegexWikiTemplate(QString &source)
    : Regex(source)
{
    QString pattern = "\\`\\{\\`\\{[^\\`]*\\`\\}\\`\\}";
    regexp.setPattern(pattern);
}


QString RegexWikiTemplate::getMatchEquivalent()
{
    qDebug() << "TEMPLATE found:" << regexp.capturedTexts();
    //No conversion is needed:
    return regexp.cap();
}
