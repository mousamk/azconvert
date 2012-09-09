#include <QDebug>
#include <QStringList>
#include "regexwikipicture.h"
#include "convertor.h"


RegexWikiPicture::RegexWikiPicture(QString &source, Convertor* convertor)
    : Regex(source), convertor(convertor)
{
    //QString pattern = "\\Şəkil:[^\\|]*\\|";         //TODO: Complete this one
    QString pattern =
            "(?:"
                "\\[\\[\\s*(?:Şəkil|File)\\s*\\:"
                "(?:([^\\]]*)\\|)*"
                "(?:([^\\]\\|]*))"
                "\\]\\]"
            ")|"
            "(?:"
                "\\n+(?:Şəkil|File)\\s*:"
                "(?:([^\\n]*)\\|)*"
                "(?:([^\\n\\|]*))"
                "(?=\\n)"
            ")"
            ;
    regexp.setPattern(pattern);
}


RegexWikiPicture::~RegexWikiPicture()
{
    delete convertor;
}


QString RegexWikiPicture::getMatchEquivalent()
{
    //Get the last part:
    QStringList list = regexp.capturedTexts();
    if (list.count() > 2)
    {
        QString prelast = list.at(1);
        QString last = list.at(2);
        //qDebug() << "last&prelast" << last << prelast;
        if(prelast.isEmpty() && last.isEmpty() && list.count()>4)
        {
            prelast = list.at(3);
            last = list.at(4);
            //qDebug() << "2nd last&prelast" << last << prelast;
        }
        //qDebug() << "PICTURE last:" << last;
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
                        "(?:\\s*upright\\s*[0-9]*(?:\\.[0-9]+)?\\s*)"
                    ")|"
                    "(?:"
                        "(?:right)|"
                        "(?:left)|"
                        "(?:center)|"
                        "(?:none)"
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
                    ")|"
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
            equivalent = "Şəkil:" + prelast + "|" + convertor->convert(last, true);
            if (list.at(0).startsWith("[["))
                equivalent = "[[" + equivalent + "]]";
            if(list.at(0).startsWith("\n"))
                equivalent = "\n" + equivalent;
            if(list.at(0).endsWith("\n"))
                equivalent += "\n";
            return equivalent;
        }
        else
            return regexp.cap();
    }

    return regexp.cap();
}
