#include <QDebug>
#include <QStringList>
#include "regexurl.h"


RegexUrl::RegexUrl(QString &source, Convertor* convertor)
    : Regex(source, convertor)
{
    QString pattern = "(?:[a-zA-Z\\+]+\\:\\/\\/)?"
                      "(?:"
                            "(?:[a-zA-Z0-9\\-]+\\.)+"
                            "[a-zA-Z]{2,2}"
                            "(?:"
                                "(?:\\-\\-[a-zA-Z0-9]+)"
                                "|"
                                "(?:[a-zA-Z]*)"
                            ")"
                            "|"
                            "(?:(?:[0-9]{1,3}\\.){3,3}(?:[0-9]{1,3}))"
                      ")"
                      "(?:\\/(?:[^\\`\\s\\}\\]\\{\\]\\[])*)?";
    regexp.setPattern(pattern);
}


QString RegexUrl::getMatchEquivalent()
{
    qDebug() << "URL Found:" << regexp.capturedTexts();
    //No conversion is needed:
    return regexp.cap();
}
