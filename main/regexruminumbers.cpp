#include <QDebug>
#include <QStringList>
#include "regexruminumbers.h"


//Allocate memory for static member variables:
QMap<QString,QString> RegexRumiNumbers::rumiNumbers;


RegexRumiNumbers::RegexRumiNumbers(QString &source)
    : Regex(source)
{
    //Initialize pattern:
    QString pattern = "(\\s+|\\-|^)"
                      "(I|II|III|IV|V|VI|VII|VIII|IX|X|XI|XII|XIII|XIV|XV|XVI|XVII|XVIII|XIX|XX|XXI|XXII|XXIII|XXIV|XXV|XXVI|XXVII|XXVIII|XXIX)"
                      "(?=\\s+|\\-|$)";
    regexp.setPattern(pattern);

    //Initialize numbers conversion map:
    if (rumiNumbers.isEmpty())
    {
        rumiNumbers["I"] = "۱-جی";
        rumiNumbers["II"] = "۲-جی";
        rumiNumbers["III"] = "۳-جو";
        rumiNumbers["IV"] = "۴-جو";
        rumiNumbers["V"] = "۵-جی";
        rumiNumbers["VI"] = "۶-جی";
        rumiNumbers["VII"] = "۷-جی";
        rumiNumbers["VIII"] = "۸-جی";
        rumiNumbers["IX"] = "۹-جو";
        rumiNumbers["X"] = "۱۰-جو";
        rumiNumbers["XI"] = "۱۱-جی";
        rumiNumbers["XII"] = "۱۲-جی";
        rumiNumbers["XIII"] = "۱۳-جو";
        rumiNumbers["XIV"] = "۱۴-جو";
        rumiNumbers["XV"] = "۱۵-جی";
        rumiNumbers["XVI"] = "۱۶-جی";
        rumiNumbers["XVII"] = "۱۷-جی";
        rumiNumbers["XVIII"] = "۱۸-جی";
        rumiNumbers["XIX"] = "۱۹-جو";
        rumiNumbers["XX"] = "۲۰-جی";
        rumiNumbers["XXI"] = "۲۱-جی";
        rumiNumbers["XXII"] = "۲۲-جی";
        rumiNumbers["XXIII"] = "۲۳-جو";
        rumiNumbers["XXIV"] = "۲۴-جو";
        rumiNumbers["XXV"] = "۲۵-جی";
        rumiNumbers["XXVI"] = "۲۶-جی";
        rumiNumbers["XXVII"] = "۲۷-جی";
        rumiNumbers["XXVIII"] = "۲۸-جی";
        rumiNumbers["XXIX"] = "۲۹-جو";
    }
}


QString RegexRumiNumbers::getMatchEquivalent()
{
    qDebug() << "Rumi number found: " << regexp.capturedTexts();

    QString num = regexp.cap(2);
    QString equivalent = regexp.cap(1);
    equivalent += rumiNumbers.contains(num) ? rumiNumbers[num] : num;

    return equivalent;
}
