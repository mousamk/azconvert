#include <QDebug>
#include <QStringList>
#include "regexwikipicture.h"
#include "convertor.h"


RegexWikiPicture::RegexWikiPicture(QString &source, Convertor* convertor)
    : Regex(source, convertor)
{
    //QString pattern = "\\Şəkil:[^\\|]*\\|";         //TODO: Complete this one
    QString pattern =
            "\\[\\[\\s*Şəkil\\s*\\:"
            "(?:([^\\]]*)\\|)*"
            "(?:([^\\]\\|]*))"
            "\\]\\]"
            ;
    regexp.setPattern(pattern);
}


QString RegexWikiPicture::getMatchEquivalent()
{
    //Get the last part:
    QStringList list = regexp.capturedTexts();
    if (list.count() > 2)
    {
        QString last = list.at(list.count()-1);
        qDebug() << "PICTURE last:" << last;
        qDebug() << "PICTURE found:" << regexp.capturedTexts();

        //Check if the last part is not a special field:
        bool transliterate = true;
        QRegExp tempRegexp(
                    "(?:\\s*alt\\s*\\=.*)|"
                    "(?:\\s*link\\s*\\=.*)|"
                    "(?:"
                        "(?:\\s*[0-9]+\\s*px\\s*)|"
                        "(?:\\s*x\\s*[0-9]+\\s*px\\s*)|"
                        "(?:\\s*[0-9]+\\s*x\\s*[0-9]+\\s*px\\s*)|"
                        "(?:\\s*upright\\s*)|"
                        "(?:\\s*upright\\s*[0-9]*(?:\\.[0-9]+)?\\s*)|"
                    ")|"
                    "(?:"
                        "\\s*(?:"
                            "(?:baseline)|"
                            "(?:middle)|"
                            "(?:sub)|"
                            "(?:super)|"
                            "(?:text\\-top)|"
                            "(?:text\\-bottom)|"
                            "(?:top)|"
                            "(?:bottom)"
                        ")\\s*"
                    ")\\|"
                    "(?:\\s*border\\s*)|"
                    "(?:"
                        "\\s*thumb(?:nail)?\\s*(?:\\=\\s*[^\\]\\|]*)?"
                    ")"
                    , Qt::CaseInsensitive);

        //If it's matches:
        if (tempRegexp.indexIn(last, 0) != -1)
        {
            //If the whole text is a match:
            if(tempRegexp.cap() == last)
                transliterate = false;
            //qDebug() << transliterate;
        }

        QString equivalent;
        if (transliterate)
        {
            equivalent = "[[Şəkil:" + regexp.cap(1) + "|" + convertor->convert(regexp.cap(2) + "]]");
            return equivalent;
        }
        else
            return regexp.cap();
    }

    //No conversion is needed:
    return regexp.cap();
}
