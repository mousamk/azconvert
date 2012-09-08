#include "regexhtmltag.h"


RegexHtmlTag::RegexHtmlTag(QString &source, Convertor* convertor)
    : Regex(source, convertor)
{
    QString pattern = "\\<[^\\>]*\\>";
    regexp.setPattern(pattern);
}


QString RegexHtmlTag::getMatchEquivalent()
{
    //No conversion is needed:
    return regexp.cap();
}
