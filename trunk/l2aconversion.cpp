#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <QHash>
#include <QRegExp>

#include "l2aconversion.h"
#include "settings.h"
#include "dbservice.h"
#include "util.h"
#include "config.h"
#include "regexurl.h"
#include "regexemail.h"
#include "regexwikitemplate.h"
#include "regexwikiinterwiki.h"
#include "regexwikipicture.h"
#include "regexhtmltag.h"
#include "regexwikilink.h"
#include "regexwikinoconvert.h"
#include "regexwikiforceconvert.h"
#include "regexwikinowiki.h"


L2AConversion::L2AConversion(QObject* parent)
    : Convertor(parent),
      eh('\x59', '\x02'),
      //ih('\x31', '\x01'),
      //Ih('\x30', '\x01'),
      //sh('\x5f', '\x01'),
      //ch('\xe7', '\x00'),
      //uh('\xfc', '\x00'),
      //oh('\xf6', '\x00'),
      //gh('\x1f', '\x01'),
      vs('\x0c', '\x20'),
      vs_str(vs)
{ 
    reloadResources();
}


QString L2AConversion::getTablesPostfix()
{
    return "_l2a";
}


bool L2AConversion::canAddWords()
{
    return true;
}


QStringList L2AConversion::getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record)
{
    QStringList tuple;
    tuple << query.value(record.indexOf("start")).toString()
          << query.value(record.indexOf("mid")).toString()
          << query.value(record.indexOf("end")).toString()
          << query.value(record.indexOf("start_voc")).toString()
          << query.value(record.indexOf("mid_voc")).toString()
          << query.value(record.indexOf("end_voc")).toString()
          << query.value(record.indexOf("front_or_back")).toString()
          << query.value(record.indexOf("vowel")).toString()
          << query.value(record.indexOf("sticking")).toString();

    return tuple;
}


Qt::LayoutDirection L2AConversion::getSourceLayoutDirection()
{
    return Qt::LeftToRight;
}


Qt::LayoutDirection L2AConversion::getDestinationLayoutDirection()
{
    return Qt::RightToLeft;
}


void L2AConversion::setOriginalText(const QString &text)
{
    Convertor::setOriginalText(text);
    this->strResult = "";
}


void L2AConversion::separatePostfixes(const QString& word, bool part, QString &nakedWord, QString &wordPostfixes)
{
    nakedWord = word;
    wordPostfixes = "";
    if (word.isEmpty())
        return;

    QString postfix;
    QStringList list;
    bool hasVs, removeLast;
    QMapIterator<int, QStringList> it(postfixes);
    int offset = part ? 0 : 3;
    while(it.hasNext())
    {
        it.next();
        list = it.value();
        postfix = list.at(0);
        hasVs = removeLast = false;

        if (nakedWord.length() >= postfix.length() + offset &&
                nakedWord.endsWith(postfix) &&
                     (list.at(3) == "0" ||
                          (list.at(3)=="1" && !lookupWord(nakedWord.left(nakedWord.length()-postfix.length())).isEmpty()
                          )
                     )
           )
        {
            if (!part)
            {
                switch (list.at(2).toInt())
                {
                    case 1:
                        //Nothing to do!
                        break;

                    case 2:
                        if (isSticking(nakedWord[nakedWord.length() - postfix.length() - 1]))
                            hasVs = true;
                        break;

                    case 3:
                        if (nakedWord[(nakedWord.length() - postfix.length()) - 1] == eh)
                            hasVs = true;
                        break;

                    case 4:
                        if (nakedWord[(nakedWord.length() - postfix.length()) - 1] == eh)
                            removeLast = true;
                        break;
                }
            }

            wordPostfixes = (hasVs ? vs_str : "") + list.at(1) + wordPostfixes;
            nakedWord = nakedWord.left(nakedWord.length()-postfix.length());
            if (removeLast && !part)
                nakedWord = nakedWord.left(nakedWord.length()-1);

            //Check if the remaining word is in dictionary:
            if (!lookupWord(nakedWord).isEmpty())
                return;
            else
            {
                it.toFront();
                continue;
            }
        }
    }
}


void L2AConversion::separatePrefixes(const QString& word, QString& nakedWord, QString& wordPrefixes)
{
    nakedWord = word;
    wordPrefixes = "";
    if (word.isEmpty())
        return;

    bool hasVs = false;
    bool removeLast = false;
    QString prefix;
    QStringList list;
    QMapIterator<int, QStringList> it(prefixes);
    while(it.hasNext())
    {
        it.next();
        list = it.value();
        prefix = list.at(0);

        if (nakedWord.length() > prefix.length() + 2 && nakedWord.startsWith(prefix))
        {
            switch (list.at(2).toInt())
            {
                case 1:
                    //Nothing to do!
                    break;

                case 2:
                    if (isSticking(prefix[prefix.length() - 1]))
                        hasVs = true;
                    break;

                case 3:
                    if (prefix[prefix.length() - 1] == eh)
                        hasVs = true;
                    break;

                case 4:
                    if (prefix[prefix.length() - 1] == eh)
                        removeLast = true;
                    break;
            }

            wordPrefixes += list.at(1);
            if (removeLast)
                wordPrefixes = wordPrefixes.left(wordPrefixes.length()-1);
            wordPrefixes += (hasVs ? vs_str : "");
            nakedWord = nakedWord.right(nakedWord.length()-prefix.length());

            //Check if the remaining word is in dictionary:
            if (!lookupWord(nakedWord).isEmpty())
                return;
            else
            {
                it.toFront();
                continue;
            }
        }
    }
}


void L2AConversion::preprocessText(bool wikiMode)
{
    //Changing "dr." to "dr ":
    strSource.replace("dr.", "dr", Qt::CaseInsensitive);

    //Escape every '\', '{' and '}' characters using `:
    strSource.replace("`", "``");
    strSource.replace("{", "`{");
    strSource.replace("}", "`}");

    //List of regex processors:
    QList<Regex*> regexProcessors;
    if (wikiMode) regexProcessors.append(new RegexWikiNoWiki(strSource, new L2AConversion(this)));
    if (wikiMode) regexProcessors.append(new RegexWikiNoConvert(strSource));
    if (wikiMode) regexProcessors.append(new RegexWikiForceConvert(strSource));
    regexProcessors.append(new RegexEmail(strSource));
    regexProcessors.append(new RegexUrl(strSource));
    if (wikiMode) regexProcessors.append(new RegexWikiTemplate(strSource));
    if (wikiMode) regexProcessors.append(new RegexWikiInterwiki(strSource));
    if (wikiMode) regexProcessors.append(new RegexWikiLink(strSource, new L2AConversion(this)));
    if (wikiMode) regexProcessors.append(new RegexWikiPicture(strSource, new L2AConversion(this)));
    regexProcessors.append(new RegexHtmlTag(strSource));


    //Run each one of the regex processors and collect its results:
    if (Regex::getHolderNumber() > 2000000000) Regex::reset();      //Just to be sure in. Here this cannot happen, but in php mode, it may!
    bool change = true;
    while(change)
    {
        change = false;
        for(int i=0; i<regexProcessors.count(); i++)
        {
            if (regexProcessors.at(i)->run())
                change = true;
            replaces.unite(regexProcessors.at(i)->getResults());
        }
    }

    //Delete the regex processors:
    for(int i=regexProcessors.count()-1; i>=0; i--)
    {
        delete regexProcessors.at(i);
        regexProcessors.removeLast();
    }
}


void L2AConversion::postprocessText()
{
    //Replace back the place holder:
    QString holder1,holder2;
    QMap<int,QString>::const_iterator i;
    bool change = true;
    while(change)
    {
        change = false;
        for(i=replaces.constBegin(); i!=replaces.constEnd(); i++)
        {
            int index = i.key();
            holder1 = "{" + convertWordSimple(QString::number(index)) + "}";
            holder2 = "{" + QString::number(index) + "}";
            //qDebug() << "checking for holder: " << holder1 << holder2;
            if(strResult.contains(holder1))
            {
                strResult.replace(holder1, i.value());
                change = true;
            }
            else if(strResult.contains(holder2))
            {
                strResult.replace(holder2, i.value());
                change = true;
            }
        }
    }

    //Remove escape characters:
    strResult.replace("`{", "{");
    strResult.replace("`}", "}");
    strResult.replace("``", "`");
}


QString L2AConversion::preprocessWord(QString word)
{
    QString res = word;

    //Add necessary 'i' to some words:
    if (res.length() > 2 &&
        (res.mid(0, 2) == ("sp") ||
        res.mid(0, 2) == ("st") ||
        res.mid(0, 2) == ("şp") ||
        res.mid(0, 2) == ("şt") ||
        res.mid(0, 2) == ("şk")))       //TODO: Not sure if this is sh or s!
        res = res.insert(0, "i");

    res.replace("iyi", "igi");
    res.replace("iyy", "iy");       //NOTE: Not sure of this!
    res.replace("iy", "i");         //NOTE: Not sure of this!

    return res;
}


/*QString L2AConversion::convert(QString text, bool wikiMode)
{
    //Preprocess text:
    preprocessText(wikiMode);

    //Convert the preprocessed text:
    return convert(NULL, text);

    //Postprocess converted text:
    postprocessText();
}*/


QString L2AConversion::convert(QProgressDialog* prg, bool wikiMode)
{
    //Pre process text:
    preprocessText(wikiMode);

    //Convert the preprocessed text:
    strResult = convert(prg, strSource);

    //Post process result:
    postprocessText();

    return strResult;
}


QString L2AConversion::convert(QProgressDialog* prg, QString text)
{
    QString res;
    int length = text.length();
    int i = 0;
    bool bracket = false;       //Beware of this in non-wiki mode!
    while (i < length)
    {
        QString word = getWord(i, text);
        bracket = i>0 && (text[i-1]==']' || text[i-1]=='}');
        i += word.length();

        if (NULL != prg)
        {
            //Set progress:
            int min = i <= length ? i : length;
            prg->setValue(min);

            //DoEvents:
            QCoreApplication::processEvents();

            //Handle cancelation:
            if (prg->wasCanceled())
                break;
        }

        res += convertWord(word, bracket);

        while ((i < length) && !isCharAInWordChar(text[i]))
        {
            QChar curChar = text[i];

            //Converting characters:
            QString ch = getSpecialChar(curChar, i);
            res += ch.isEmpty() ? QString(curChar) : ch;
            i++;
        }
    }

    return res;
}


QString L2AConversion::convertWord(const QString& w, bool part)
{
    if (w.isEmpty())
        return "";

    if (!part && isNonConvertableWord(w))
        return w;


    QString word;
    WORD_TO_LOWER(w, word);
    QString str = "";
    if (!part) str = lookupWord(word);
    if (str.isEmpty())
    {
        //Separate and convert prefixes:
        QString wordWithoutPrefixes = word;
        QString wordPrefixes, wordDict;
        if (!part)
        {
            separatePrefixes(word, wordWithoutPrefixes, wordPrefixes);

            //Check remaning in dictionary:
            wordDict = lookupWord(wordWithoutPrefixes);
            if (!wordDict.isEmpty())
            {
                str = wordPrefixes + wordDict;
                return str;
            }
        }

        //Separate and convert postfixes:
        QString wordWithoutPostfixes;
        QString wordPostfixes;
        separatePostfixes(wordWithoutPrefixes, part, wordWithoutPostfixes, wordPostfixes);

        //Check remaining in dictionary:
        if (!part)
        {
            wordDict = lookupWord(wordWithoutPostfixes);
            if (!wordDict.isEmpty())
            {
                str = wordPrefixes + wordDict + wordPostfixes;
                return str;
            }
        }

        //Stick them together and form the final word:
        word = wordPrefixes + wordWithoutPostfixes + wordPostfixes;

        //Preprocess word:
        word = preprocessWord(word);

        //Use simple transliteration to convert the rest:
        str = convertWordSimple(word);
    }
    
    return str;
}


QString L2AConversion::convertWordSimple(const QString &word)
{
    QString str = "";
    int length = word.length();
    for (int i = 0; i < length; i++)
    {
        //Choose letter position mode:
        int modeIndex;
        if (0 == i) modeIndex = 0;
        else if (length-1 == i) modeIndex = 2;
        else modeIndex = 1;
        //TODO: Consider 'voc' modes too

        QChar c = word[i];
        QString eq;
        getCharEquivalent(c, modeIndex, eq);
        str += eq;
    }

    return str;
}


void L2AConversion::getCharEquivalent(const QChar &ch, int columnIndex, QString &equivalent)
{
    equivalent = chars.contains(ch) ? chars.value(ch).at(columnIndex) : QString(ch);
}


QString L2AConversion::getSpecialChar(QChar c, int index)
{
    QMap<int, SpecialCharacterRecord>::const_iterator i;
    for(i = specialChars.constBegin(); i != specialChars.constEnd(); i++)
    {
        if(i.value().source == QString(c))
        {
            int position = i.value().position;
            if (Neutral == position)
                return i.value().equivalent;
            else
            {
                int times = getCharacterCount(c, index);
                if ((Opening == position && !IS_EVEN(times)) || (Closing == position && IS_EVEN(times)))
                    return i.value().equivalent;
            }
        }
    }

    return "";
}


int L2AConversion::getCharacterCount(QChar character, int position)
{
    return strSource.left(position+1).count(character);
}


QString L2AConversion::getWord(int i, QString source)
{
    QString word = "";
    QChar c = source[i];
    int len = source.length();

    while (isCharAInWordChar(c))
    {
        word += QString(c);
        i++;

        if (i >= len)
            break;

        c = source[i];
    }

    return word;
}


QString L2AConversion::lookupWord(const QString& w)
{
    QString res = words.contains(w) ? words.value(w) : "";
    return res;
}


bool L2AConversion::isCharAInWordChar(QChar c)
{
    QChar cLower;
    CHAR_TO_LOWER(c, cLower);
    return chars.contains(cLower)               //It's in the characters table
            || c.isDigit()                      //It's a digit
            || 'w' == cLower;                   //It has 'w'. This is necessary because this letter is not in characters table
}


bool L2AConversion::isNonConvertableWord(const QString& w)
{
    QString lw;
    WORD_TO_LOWER(w, lw);
    return lw.contains("w") || solidWords.contains(lw);
}


bool L2AConversion::isSticking(QChar c)
{
    bool sticking = true;
    if (chars.contains(c)) sticking = chars.value(c).at(8) != "0";

    return sticking;
}

