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
      ih('\x31', '\x01'),
      Ih('\x30', '\x01'),
      //sh('\x5f', '\x01'),
      //ch('\xe7', '\x00'),
      uh('\xfc', '\x00'),
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
    loadPrefixes();
    loadPostfixes();
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


void L2AConversion::PreprocessText()
{
    /*//Changing "dr." to "dr "
    while (strSource.contains("dr.", Qt::CaseSensitive))
    {
        int index = strSource.indexOf("dr.");
        strSource = strSource.mid(0, index + 2) + " " + strSource.mid(index + 3, strSource.length() - (index + 3));
    }

    //Changing "Dr." to "Dr "
    while (strSource.contains("Dr.", Qt::CaseSensitive))
    {
        int num2 = strSource.indexOf("Dr.");
        strSource = strSource.mid(0, num2 + 2) + " " + strSource.mid(num2 + 3, strSource.length() - (num2 + 3));
    }

    //Changing "DR." to "DR "
    while (strSource.contains("DR.", Qt::CaseSensitive))
    {
        int num3 = strSource.indexOf("DR.");
        strSource = strSource.mid(0, num3 + 2) + " " + strSource.mid(num3 + 3, strSource.length() - (num3 + 3));
    }*/
}


QString L2AConversion::convert(QProgressDialog* prg)
{
    //Load wiki mode:
    //bool wikiMode = Settings::GetInstance(this->parent())->GetWikiMode();

    //These variables are used in wiki mode:
    //int doubleBracket=0;
    //bool openBracketSeen = false;
    //bool closeBracketSeen = false;

    PreprocessText();

    int length = strSource.length();
    int i = 0;
    while (i < length)
    {
        QString word = GetWord(i);
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
            strResult += convertWord(word, true);
        //else
        //    strResult += word;


        while ((i < length) && !IsCharAInWordChar(strSource[i]))
        {
            QChar curChar = strSource[i];
            /*//Wikimode:
            //*********** Counting double brackets used in wiki format: ************
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
            //******************* End counting double brakcets: *********************/


            //Converting characters:
            QChar ch = GetSpecialChar(curChar);
            if (ch != ' ')
                strResult = strResult + QString(ch);
            else
                strResult = strResult + QString(curChar);
            i++;
        }
    }

    return strResult;
}


//This function is used in for 'Wiki' mode
bool L2AConversion::IsThereColonBeforeDoubleCloseBrackets(int index)
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
}


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


QString L2AConversion::convertWord(const QString& wo, bool isRecursive)
{
    QString word(wo);
    if (word.isEmpty())
        return "";

    if (IsNonConvertableWord(word))
        return word;


    word = word.replace(Ih, 'i', Qt::CaseSensitive);
    word = word.toLower();
    QString str("");
    str = lookupWord(word);
    if (str == "")
    {
        if (isRecursive)
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
        }
        if (word.length() > 2 &&
            (word.mid(0, 2) == ("sp") ||
            word.mid(0, 2) == ("st") ||
            word.mid(0, 2) == ("sp") ||
            word.mid(0, 2) == ("st") ||
            word.mid(0, 2) == ("sk")))
            word = word.insert(0, "i");
        if (word.contains("iyi"))
        {
            int index = word.indexOf("iyi");
            word = word.mid(0, index + 1) + "g" + word.mid(index + 2, word.length() - (index + 2));
        }
        if (word.contains(QString(uh)+"y"+QString(uh)))
        {
            int num2 = word.indexOf(QString(uh)+"y"+QString(uh));
            word = word.mid(0, num2 + 1) + "g" + word.mid(num2 + 2, word.length() - (num2 + 2));
        }
        if (word.contains("iyy"))
        {
            int num3 = word.indexOf("iyy");
            word = word.mid(0, num3) + word.mid(num3 + 2, word.length() - (num3 + 2));
        }
        if (word.contains("iy"))
        {
            int num4 = word.indexOf("iy");
            word = word.mid(0, num4) + word.mid(num4 + 1, word.length() - (num4 + 1));
        }

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
    qDebug() << "char: " << ch;
    //TODO: Why arabic scripts are comming to this function?!

    if (chars.contains(ch))
        equivalent = chars.value(ch).at(columnIndex);
    else
        //Now that no equivalent is found, return the same source:
        equivalent = QString(ch);
}


QString L2AConversion::GetResult()
{
    return strResult;
}

QChar L2AConversion::GetSpecialChar(QChar c)
{
    if (c == ',')
        return QChar('\x0c', '\x06');
    else if (c ==  ';')
        return QChar('\x1b', '\x06');
    else if (c == '?')
        return QChar('\x1f', '\x06');

    return ' ';
}


/*QString L2AConversion::GetWord(int i, QChar delim)
{
}*/


QString L2AConversion::GetWord(int i)
{
    QString word = "";
    QChar c = strSource[i];
    int len = strSource.length();

    //Checking if the text ahead is URL:
    bool isURL = false;
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
    }
    //End of processing URL!

    while (IsCharAInWordChar(c))
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
    if (words.contains(w))
        res = words.value(w);
    else
        res = "";

    qDebug() << "Looking up: " << w << "result: " << res;

    return res;
}


bool L2AConversion::IsBackVowel(QChar c)
{
    bool back = chars.contains(c) ? chars.value(c).at(6) == "2" : false;
    qDebug() << c << " is a back vowel: " << back;

    return back;
}


bool L2AConversion::IsCharAInWordChar(QChar c)
{
    QChar cLower;
    CHAR_TO_LOWER(c, cLower);
    return chars.contains(cLower) || c.isDigit();
}


bool L2AConversion::IsFrontVowel(QChar c)
{
    bool front = chars.contains(c) ? chars.value(c).at(6) == "1" : false;
    qDebug() << c << " is a front vowel: " << front;

    return front;
}


bool L2AConversion::IsNonConvertableWord(const QString& w)
{
    return (w.contains("w") || w.contains("W") || w == ("I")
         || w == (Ih) || w.toUpper() == ("II") || w.toUpper() == (QString(Ih)+QString(Ih))
         || w.toUpper() == ("III") || w.toUpper() == (QString(Ih)+QString(Ih)+QString(Ih)) || w.toUpper() == ("IV")
         || w.toUpper() == (QString(Ih)+"V") || w.toUpper() == ("V") || w.toUpper() == ("VI")
         || w.toUpper() == ("V"+QString(Ih)) || w.toUpper() == ("VII") || w.toUpper() == ("V"+QString(Ih)+QString(Ih))
         || w.toUpper() == ("VIII") || w.toUpper() == ("V"+QString(Ih)+QString(Ih)+QString(Ih)) || w.toUpper() == ("IX")
         || w.toUpper() == (QString(Ih)+"X") || w.toUpper() == ("X") || w.toUpper() == ("XX")
         || w.toUpper() == ("XXI") || w.toUpper() == ("XX"+QString(Ih)) || w.toUpper() == ("XI")
         || w.toUpper() == ("X"+QString(Ih)) || w.toUpper() == ("XII") || w.toUpper() == ("X"+QString(Ih)+QString(Ih))
         || w.toUpper() == ("XIII") || w.toUpper() == ("X"+QString(Ih)+QString(Ih)+QString(Ih)) || w.toUpper() == ("XIV")
         || w.toUpper() == ("X"+QString(Ih)+"V") || w.toUpper() == ("XV") || w.toUpper() == ("XVI")
         || w.toUpper() == ("XV"+QString(Ih)) || w.toUpper() == ("XVII") || w.toUpper() == ("XV"+QString(Ih)+QString(Ih))
         || w.toUpper() == ("XVIII") || w.toUpper() == ("XV"+QString(Ih)+QString(Ih)+QString(Ih)) || w.toUpper() == ("XIX")
         || w.toUpper() == ("X"+QString(Ih)+"X") || w.toUpper() == ("C++") || w.toUpper() == ("NOTEPAD")
         || w.toUpper() == ("C#") || w.toUpper() == ("NET") || w.toUpper() == ("XP")
         || w.toUpper() == ("BASIC") || w.toUpper() == ("FILE") || w.toUpper() == ("EDIT")
         || w.toUpper() == ("PROPERTIES"));
}


bool L2AConversion::IsVowel(QChar c)
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
}


bool L2AConversion::isSticking(QChar c)
{
    bool sticking = true;
    if (chars.contains(c)) sticking = chars.value(c).at(8) != "0";
    qDebug() << c << " is sticking to the next character: " << sticking;

    return sticking;
}

