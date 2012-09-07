#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <QHash>

#include "l2aconversion.h"
#include "settings.h"
#include "dbservice.h"
#include "util.h"


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


QString L2AConversion::convert(QProgressDialog* prg)
{
    //Load wiki mode:
    //bool wikiMode = Settings::GetInstance(this->parent())->GetWikiMode();

    //These variables are used in wiki mode:
    //int doubleBracket=0;
    //bool openBracketSeen = false;
    //bool closeBracketSeen = false;

    preprocessText();

    int length = strSource.length();
    int i = 0;
    while (i < length)
    {
        QString word = getWord(i);
        i += word.length();

        //Set progress:
        if (i <= length)
            prg->setValue(i);
        else
            prg->setValue(length);

        //DoEvents:
        QCoreApplication::processEvents();

        //Handle cancelation:
        if (prg->wasCanceled())
            break;


        //In 'Wiki' mode, don't convert the texts between double brackets
        //if (!wikiMode || (doubleBracket == 0 || !IsThereColonBeforeDoubleCloseBrackets(i)))
        strResult += convertWord(word);
        //else
        //    strResult += word;


        while ((i < length) && !isCharAInWordChar(strSource[i]))
        {
            QChar curChar = strSource[i];
            /*//Wikimode:
            // *********** Counting double brackets used in wiki format: ************
            if (curChar == '[')
            {
                if (openBracketSeen)
                {
                    openBracketSeen = false;
                    doubleBracket++;
                }
                else
                    openBracketSeen = true;
            }
            else
                openBracketSeen = false;

            if (curChar == ']')
            {
                if (closeBracketSeen)
                {
                    closeBracketSeen = false;
                    if (doubleBracket > 0)
                        doubleBracket--;
                }
                else
                    closeBracketSeen = true;
            }
            else
                closeBracketSeen = false;
            // ******************* End counting double brakcets: *********************/


            //Converting characters:
            QString ch = getSpecialChar(curChar, i);
            strResult += ch.isEmpty() ? QString(curChar) : ch;
            i++;
        }
    }

    return strResult;
}


//This function is used in for 'Wiki' mode
/*bool L2AConversion::IsThereColonBeforeDoubleCloseBrackets(int index)
{
    int count = strSource.length();
    for (int i=index; i<count; i++)
    {
        if (strSource[i] == ']' && i>0 && strSource[i-1] == ']')
            return false;
        else if (strSource[i] == '|')
            return false;
        else if (strSource[i] == ':')
            return true;
    }

    return false;
}*/


/*QString L2AConversion::ConvertHtml()
{
    //TODO: PreprocessText();
    //TODO: Complete and debug this function

    int len = strSource.length();
    int i=0;
    int ob = 0;     //Open '<'s
    while(i < len)
    {
        if (strSource[i] == '<')
        {
            ob++;
            strResult += strSource[i++];
            continue;
        }
        else if (strSource[i] == '>')
        {
            ob--;
            strResult += strSource[i++];
            continue;
        }
        else if (ob != 0)
        {
            strResult += strSource[i++];
            continue;
        }


        QString word = GetWord(i);
        i += word.length();
        strResult = strResult + ConvertWord(word, true);
        while ((i < len) && !IsCharAInWordChar(strSource[i]))
        {
            QChar ch = GetSpecialChar(strSource[i]);
            if (ch != ' ')
                strResult += QString(ch);
            else
                strResult += QString(strSource[i]);
            i++;
        }
    }
}*/


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

        str = "";
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


QString L2AConversion::getWord(int i)
{
    QString word = "";
    QChar c = strSource[i];
    int len = strSource.length();

    //TODO: Find a better way to detect URLs.
    //Checking if the text ahead is URL:
    /*bool isURL = false;
    if (len - i > 4 && strSource.mid(i, 4).toLower() == ("www."))
    {
        int dot = 0;
        int j = i;
        c = strSource[j];
        while (c == '.' || IsCharAInWordChar(c) || j < len)
        {
            if (c == '.')
                dot++;
            j++;
            if (j >= len) break;
            c = strSource[j];
        }
        if (dot > 1)
            isURL = true;
    }
    if (isURL)
    {
        c = strSource[i];
        int dot = 0;
        do
        {
            if (c == '.' && (i >= len - 1 || strSource[i + 1] == ' '))
                break;

            if (c == '.')
                dot++;
            word += QString(c);
            i++;
            if (i >= len) break;
            c = strSource[i];
        } while (c == '.' || IsCharAInWordChar(c));

        return word;
    }*/
    //End of processing URL!

    while (isCharAInWordChar(c))
    {
        word = word + QString(c);
        i++;

        if (i >= len)
            break;

        c = strSource[i];
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
    return chars.contains(cLower) || c.isDigit();
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
    qDebug() << c << " is sticking to the next character: " << sticking;

    return sticking;
}

