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


void L2AConversion::reloadResources()
{
    loadChars();
    loadWords();
    loadSolidWords();
    loadPrefixes();
    loadPostfixes();
    loadSpecialChars();
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


void L2AConversion::separatePostfixes(const QString& word, QString &nakedWord, QString &wordPostfixes)
{
    nakedWord = word;
    wordPostfixes = "";
    if (word.isEmpty())
        return;

    QString postfix;
    QStringList list;
    bool hasVs = false;
    bool removeLast = false;
    QMapIterator<int, QStringList> it(postfixes);
    while(it.hasNext())
    {
        it.next();
        list = it.value();
        postfix = list.at(0);
        hasVs = removeLast = false;

        if (nakedWord.length() > postfix.length() + 2 &&
                nakedWord.endsWith(postfix) &&
                     (list.at(3) == "0" ||
                          (list.at(3)=="1" && !lookupWord(nakedWord.left(nakedWord.length()-postfix.length())).isEmpty()
                          )
                     )
           )
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

            wordPostfixes = (hasVs ? vs_str : "") + list.at(1) + wordPostfixes;
            nakedWord = nakedWord.left(nakedWord.length()-postfix.length());
            if (removeLast)
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

            //TODO: Instead of line below, check the list.at(2) and do the right work.
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


void L2AConversion::preprocessText()
{
    //Changing "dr." to "dr ":
    strSource.replace("dr.", "dr", Qt::CaseInsensitive);

    //Escape every '\', '{' and '}' characters using `:
    strSource.replace("`", "``");
    strSource.replace("{", "`{");
    strSource.replace("}", "`}");

    //List of regex processors:
    QList<Regex*> regexProcessors;
    regexProcessors.append(new RegexUrl(strSource, this));
    regexProcessors.append(new RegexEmail(strSource, this));
    regexProcessors.append(new RegexWikiTemplate(strSource, this));
    regexProcessors.append(new RegexWikiInterwiki(strSource, this));
    regexProcessors.append(new RegexWikiLink(strSource, this));
    regexProcessors.append(new RegexWikiPicture(strSource, this));      //NOTE: Needs completion
    regexProcessors.append(new RegexHtmlTag(strSource, this));
    //add others...

    //Run each one of the regex processors and collect its results:
    Regex::reset();
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

    //Find urls:
    //QString wikiNoConvert   = "(?:\\`\\{\\`\\{" + QString(WIKI_NO_CONVERT_TAG) + "\\s*\\|.*\\`\\}\\`\\})";         //TODO: Beware of this in non-wiki mode.
    /*QString wikiTemplate    = "(?:\\`\\{\\`\\{[^\\`]*\\`\\}\\`\\})";       //TODO: Beware of this in non-wiki mode.    //TODO: This generalizes the wikiNoConvert. So in this situation, it's not needed!   //TODO: Beware when a ` character is in the middle!
    QString wikiInterwiki   = "(?:\\[\\[[a-zA-Z\\-]+\\:[^\\]]*\\]\\])";           //TODO: Beware of this in non-wiki mode.
    QString wikiPicture     = "(?:\\Şəkil:[^\\|]*\\|)";           //TODO: Beware of this in non-wiki mode. //TODO: Beware of the last necessary | character. It maybe sometimes missing!
    QString htmlTag         = "(?:\\<[^\\>]*\\>)";       //TODO: Beware of this in non-html mode.

    QString allRegexStr = urlRegexStr + "|" + emailRegexStr + "|" + wikiNoConvert + "|" + htmlTag
            + "|" + wikiInterwiki + "|" + wikiPicture + "|" + wikiTemplate;
    QRegExp regExp(allRegexStr, Qt::CaseInsensitive);
    int index = 0;
    QString match;
    QString holder;
    int count=0;
    bool change = true;
    while(change)
    {
        index = 0;
        change = false;
        while((index = regExp.indexIn(strSource, index)) != -1)
        {
            match = regExp.cap();
            qDebug() << "found a match: " << match << " at position: " << index;

            //Replace the url with a numbered place holder:
            replaces.insert(count, match);
            holder = "{" + QString::number(count) + "}";
            strSource.replace(index, match.length(), holder);
            count++;
            index += holder.length();
            change = true;
        }
    }

    //Find wiki links:
    QString wikiLinkSimple  = "(?:\\[\\[([^\\|\\]]+)(?:\\|([^\\]]+))?\\]\\])";       //TODO: Beware of this in non-wiki mode.
    QRegExp customRegExp(wikiLinkSimple, Qt::CaseInsensitive);
    index = 0;
    QString link, link1, link2, equivalent, fullEqual;
    //qDebug() << "source now: " <<strSource;
    while((index = customRegExp.indexIn(strSource, index)) != -1)
    {
        match = customRegExp.cap();
        link1 = customRegExp.cap(1);
        link2 = customRegExp.cap(2);
        link = link2.isEmpty() ? link1 : link2;
        equivalent = convert(NULL, link);
        fullEqual = "[[" + link1 + "|" + equivalent + "]]";

        //qDebug() << "found a simple link: " << match << link1 << "|" << link2 << equivalent << fullEqual << "at index:" << index;

        replaces.insert(count, fullEqual);
        holder = "{" + QString::number(count) + "}";
        strSource.replace(index, match.length(), holder);
        count++;
        index += holder.length();
    }*/
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
        res.mid(0, 2) == ("sp") ||
        res.mid(0, 2) == ("st") ||
        res.mid(0, 2) == ("sk")))
        res = res.insert(0, "i");

    res.replace("iyi", "igi");
    res.replace("iyy", "iy");       //NOTE: Not sure of this!
    res.replace("iy", "i");         //NOTE: Not sure of this!

    return res;
}


QString L2AConversion::convert(QString text)
{
    return convert(NULL, text);
}


QString L2AConversion::convert(QProgressDialog* prg)
{
    //Load wiki mode:
    //bool wikiMode = Settings::GetInstance(this->parent())->GetWikiMode();

    //Pre process text:
    preprocessText();

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
    while (i < length)
    {
        QString word = getWord(i, text);
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

        res += convertWord(word);

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


QString L2AConversion::convertWord(const QString& w)
{
    if (w.isEmpty())
        return "";

    if (isNonConvertableWord(w))
        return w;


    QString word;
    WORD_TO_LOWER(w, word);
    QString str = lookupWord(word);
    if (str.isEmpty())
    {
        //Separate and convert prefixes:
        QString wordWithoutPrefixes;
        QString wordPrefixes;
        separatePrefixes(word, wordWithoutPrefixes, wordPrefixes);

        //Check remaning in dictionary:
        QString wordDict = lookupWord(wordWithoutPrefixes);
        if (!wordDict.isEmpty())
        {
            str = wordPrefixes + wordDict;
            return str;
        }

        //Separate and convert postfixes:
        QString wordWithoutPostfixes;
        QString wordPostfixes;
        separatePostfixes(wordWithoutPrefixes, wordWithoutPostfixes, wordPostfixes);

        //Check remaining in dictionary:
        wordDict = lookupWord(wordWithoutPostfixes);
        if (!wordDict.isEmpty())
        {
            str = wordPrefixes + wordDict + wordPostfixes;
            return str;
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


QString L2AConversion::getResult()
{
    return strResult;
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
    if (source.isNull())
        source = strSource;

    QString word = "";
    QChar c = source[i];
    int len = source.length();

    while (isCharAInWordChar(c))
    {
        word = word + QString(c);
        i++;

        if (i >= len)
            break;

        c = source[i];
    }

    return word;
}


QString L2AConversion::lookupWord(const QString& w)
{
    QString res;
    res = words.contains(w) ? words.value(w) : "";

    //qDebug() << "Looking up: " << w << "result: " << res;

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


/*bool L2AConversion::isBackVowel(QChar c)
{
    bool back = chars.contains(c) ? chars.value(c).at(6) == "2" : false;
    qDebug() << c << " is a back vowel: " << back;

    return back;
}


bool L2AConversion::isFrontVowel(QChar c)
{
    bool front = chars.contains(c) ? chars.value(c).at(6) == "1" : false;
    qDebug() << c << " is a front vowel: " << front;

    return front;
}*/


bool L2AConversion::isNonConvertableWord(const QString& w)
{
    QString lw;
    WORD_TO_LOWER(w, lw);
    return lw.contains("w") || solidWords.contains(lw);
}


/*bool L2AConversion::isVowel(QChar c)
{
    bool vowel = chars.contains(c) ? chars.value(c).at(7) == "1" : false;
    qDebug() << c << " is a vowel: " << vowel;

    return vowel;
}


bool L2AConversion::isConsonant(QChar c)
{
    bool consonant = chars.contains(c) ? chars.value(c).at(7) == "0" : false;
    qDebug() << c << " is a consonant: " << consonant;

    return consonant;
}*/


bool L2AConversion::isSticking(QChar c)
{
    bool sticking = true;
    if (chars.contains(c)) sticking = chars.value(c).at(8) != "0";
    //qDebug() << c << " is sticking to the next character: " << sticking;

    return sticking;
}

