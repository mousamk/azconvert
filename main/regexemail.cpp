#include "regexemail.h"


RegexEmail::RegexEmail(QString &source)
    : Regex(source)
{
    QString pattern = "[a-zA-Z0-9_][a-zA-Z0-9_\\.]*"
                      "\\@"
                      "(?:[a-zA-Z0-9\\-]+\\.)+"
                      "[a-zA-Z]{2,2}"
                      "(?:"
                          "(?:\\-\\-[a-zA-Z0-9]+)"
                          "|"
                          "(?:[a-zA-Z]*)"
                      ")";
    regexp.setPattern(pattern);
}


QString RegexEmail::getMatchEquivalent()
{
    //No conversion is needed:
    return regexp.cap();
}
