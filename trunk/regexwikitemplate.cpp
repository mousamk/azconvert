#include "regexwikitemplate.h"


RegexWikiTemplate::RegexWikiTemplate(QString &source, Convertor* convertor)
    : Regex(source, convertor)
{
    QString pattern = "\\`\\{\\`\\{[^\\`]*\\`\\}\\`\\}";
    regexp.setPattern(pattern);
}


QString RegexWikiTemplate::getMatchEquivalent()
{
    //No conversion is needed:
    return regexp.cap();
}
