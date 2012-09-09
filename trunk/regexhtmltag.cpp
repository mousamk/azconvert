#include "regexhtmltag.h"


RegexHtmlTag::RegexHtmlTag(QString &source)
    : Regex(source)
{
    QString pattern = "\\<[^\\>]*\\>";
    regexp.setPattern(pattern);
}


QString RegexHtmlTag::getMatchEquivalent()
{
    //No conversion is needed:
    return regexp.cap();
}
