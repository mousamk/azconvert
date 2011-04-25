#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QCoreApplication>

#include "l2aconversion.h"
#include "settings.h"


L2AConversion::L2AConversion()
        :
        eh('\x59', '\x02'),
        ih('\x31', '\x01'),
        Ih('\x30', '\x01'),
        sh('\x5f', '\x01'),
        ch('\xe7', '\x00'),
        uh('\xfc', '\x00'),
        oh('\xf6', '\x00'),
        gh('\x1f', '\x01'),
        vs('\x0c', '\x20')
{
    OpenDicts();
}


QString L2AConversion::ChangePostfixes(const QString& word)
{
    QString w(word);
    QString str(word);

    if ((str = CheckPostfix(w, "p"+QString(eh)+"r"+QString(eh)+"st", 2)) != (w) ||
        (str = CheckPostfix(w, "baran", 2)) != (w) ||
        (str = CheckPostfix(w, "s"+QString(uh)+"nas", 2)) != (w) ||
        (str = CheckPostfix(w, "xana", 2)) != (w) ||
        (str = CheckPostfix(w, "p"+QString(eh)+"rv"+QString(eh)+"r", 2)) != (w) ||
        (str = CheckPostfix(w, "t"+QString(eh)+"l"+QString(eh)+"b", 2)) != (w) ||
        (str = CheckPostfix(w, "f"+QString(uh)+"ru"+QString(sh), 2)) != (w) ||
        (str = CheckPostfix(w, "dar", 3)) != (w) ||
        (str = CheckPostfix(w, "xah", 2)) != (w) ||
        (str = CheckPostfix(w, "b\u0259x\u015f", 2)) != w ||
        (str = CheckPostfix(w, "sev"+QString(eh)+"r", 2)) != (w))
        return str;


    //"l?rimd?n":
    if ((w.length() > 10) && w.endsWith("l"+QString(eh)+"rimd"+QString(eh)+"n", Qt::CaseSensitive))
        w.insert((w.length() - 8) + 5, QString(vs));
    if ((str = CheckPostfix(w, "l"+QString(eh)+"rim"+QString(vs)+"d"+QString(eh)+"n", 2)) != (w))
        return str;

    //"larimdan":
    if ((w.length() > 10) && w.endsWith("lar"+QString(ih)+"mdan", Qt::CaseSensitive))
        w.insert((w.length() - 5) + 5, vs);
    if ((str = CheckPostfix(w, "lar"+QString(ih)+"m"+QString(vs)+"dan", 2)) != (w))
        return str;

    //"l?rivd?n" & "larivdan":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"rivd"+QString(eh)+"n", 2)) != (w) ||
        (str = CheckPostfix(w, "lar"+QString(ih)+"vdan", 2)) != (w))
        return str;

    //"l?rind?n":
    if ((w.length() > 10) && w.endsWith("l"+QString(eh)+"rind"+QString(eh)+"n", Qt::CaseSensitive))
        w.insert((w.length() - 8) + 5, vs);
    if ((str = CheckPostfix(w, "l"+QString(eh)+"rin"+QString(vs)+"d"+QString(eh)+"n", 2)) != (w))
        return str;

    //"larindan":
    if ((w.length() > 10) && w.endsWith("lar"+QString(ih)+"ndan", Qt::CaseSensitive))
        w.insert((w.length() - 5) + 5, vs);
    if ((str = CheckPostfix(w, "larin"+QString(vs)+"dan", 2)) != (w))
        return str;

    //"l?rimizd?n" & "larimizdan":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"rimizd"+QString(eh)+"n", 2)) != (w) ||
        (str = CheckPostfix(w, "lar"+QString(ih)+"m"+QString(ih)+"zdan", 2)) != (w))
        return str;

    //"l?rinizd?n" & "larinizdan":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"rinizd"+QString(eh)+"n", 2)) != (w) ||
        (str = CheckPostfix(w, "lar"+QString(ih)+"n"+QString(ih)+"zdan", 2)) != (w))
        return str;


    if ((str = CheckPostfix(w, "l"+QString(eh)+"nir"+QString(eh)+"m", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nirs"+QString(eh)+"n", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nir", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nirik", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nirsiniz", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nirsiz", 2)) != (w) ||
        (str = CheckPostfix(w, "lan"+QString(ih)+"ram", 2)) != (w) ||
        (str = CheckPostfix(w, "lan"+QString(ih)+"rsan", 2)) != (w) ||
        (str = CheckPostfix(w, "lan"+QString(ih)+"r", 2)) != (w) ||
        (str = CheckPostfix(w, "lan"+QString(ih)+"r"+QString(ih)+"q", 2)) != (w) ||
        (str = CheckPostfix(w, "lan"+QString(ih)+"rs"+QString(ih)+"n"+QString(ih)+"z", 2)) != (w) ||
        (str = CheckPostfix(w, "lan"+QString(ih)+"rs"+QString(ih)+"z", 2)) != (w))
        return str;


    if ((str = CheckPostfix(w, "l"+QString(eh)+"nmir"+QString(eh)+"m", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nmirs"+QString(eh)+"n", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nmir", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nmirik", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nmirsiniz", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(eh)+"nmirsiz", 2)) != (w) ||
        (str = CheckPostfix(w, "lanm"+QString(ih)+"ram", 2)) != (w) ||
        (str = CheckPostfix(w, "lanm"+QString(ih)+"rsan", 2)) != (w) ||
        (str = CheckPostfix(w, "lanm"+QString(ih)+"r", 2)) != (w) ||
        (str = CheckPostfix(w, "lanm"+QString(ih)+"r"+QString(ih)+"q", 2)) != (w) ||
        (str = CheckPostfix(w, "lanm"+QString(ih)+"rs"+QString(ih)+"n"+QString(ih)+"z", 2)) != (w) ||
        (str = CheckPostfix(w, "lanm"+QString(ih)+"rs"+QString(ih)+"z", 2)) != (w))
        return str;


    if ((str = CheckPostfix(w, "ir"+QString(eh)+"m", 1)) != (w) ||
        (str = CheckPostfix(w, "irs"+QString(eh)+"n", 1)) != (w) ||
        (str = CheckPostfix(w, "irik", 1)) != (w) ||
        (str = CheckPostfix(w, "irsiniz", 1)) != (w) ||
        (str = CheckPostfix(w, "irsiz", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"ram", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rsan", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"r"+QString(ih)+"q", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rs"+QString(ih)+"n"+QString(ih)+"z", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rs"+QString(ih)+"z", 1)) != (w))
        return str;


    if ((str = CheckPostfix(w, "mir"+QString(eh)+"m", 1)) != (w) ||
        (str = CheckPostfix(w, "mirs"+QString(eh)+"n", 1)) != (w) ||
        (str = CheckPostfix(w, "mirik", 1)) != (w) ||
        (str = CheckPostfix(w, "mirsiniz", 1)) != (w) ||
        (str = CheckPostfix(w, "mirsiz", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"ram", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rsan", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"r"+QString(ih)+"q", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rs"+QString(ih)+"n"+QString(ih)+"z", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rs"+QString(ih)+"z", 1)) != (w))
        return str;


    if ((str = CheckPostfix(w, "irdim", 1)) != (w) ||
        (str = CheckPostfix(w, "irdin", 1)) != (w) ||
        (str = CheckPostfix(w, "irdi", 1)) != (w) ||
        (str = CheckPostfix(w, "irdik", 1)) != (w) ||
        (str = CheckPostfix(w, "irdiniz", 1)) != (w) ||
        (str = CheckPostfix(w, "irdiz", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rd"+QString(ih)+"m", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rd"+QString(ih)+"n", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rd"+QString(ih), 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rd"+QString(ih)+"q", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rd"+QString(ih)+"n"+QString(ih)+"z", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"rd"+QString(ih)+"z", 1)) != (w))
        return str;


    if ((str = CheckPostfix(w, "mirdim", 1)) != (w) ||
        (str = CheckPostfix(w, "mirdin", 1)) != (w) ||
        (str = CheckPostfix(w, "mirdi", 1)) != (w) ||
        (str = CheckPostfix(w, "mirdik", 1)) != (w) ||
        (str = CheckPostfix(w, "mirdiniz", 1)) != (w) ||
        (str = CheckPostfix(w, "mirdiz", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rd"+QString(ih)+"m", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rd"+QString(ih)+"n", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rd"+QString(ih), 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rd"+QString(ih)+"q", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rd"+QString(ih)+"n"+QString(ih)+"z", 1)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"rd"+QString(ih)+"z", 1)) != (w))
        return str;


    //eh in dict:
    if ((str = CheckPostfix(w, QString(eh), 1)) != (w) && (GetWordFromDictionary(w.mid(0, w.length() - 1)) != ""))
        return str;

    //"i" in dict:
    if ((str = CheckPostfix(w, "i", 1)) != (w) && (GetWordFromDictionary(w.mid(0, w.length() - 1)) != ""))
        return str;

    //"a" in dict:
    if ((str = CheckPostfix(w, "a", 1)) != (w) && (GetWordFromDictionary(w.mid(0, w.length() - 1)) != ""))
        return str;

    //QString(ih) in dict:
    if ((str = CheckPostfix(w, QString(ih), 1)) != (w) && (GetWordFromDictionary(w.mid(0, w.length() - 1)) != ""))
        return str;


    //"li/4":
    if ((str = CheckPostfix(w, "li", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(ih), 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(uh), 2)) != (w) ||
        (str = CheckPostfix(w, "lu", 2)) != (w))
        return str;


    //"l?" & "la":
    if ((str = CheckPostfix(w, "l"+QString(eh), 3)) != (w) ||
        (str = CheckPostfix(w, "la", 3)) != (w))
        return str;


    //"çi/4":
    if ((str = CheckPostfix(w, "çi", 2)) != (w) ||
        (str = CheckPostfix(w, "ç"+QString(ih), 2)) != (w) ||
        (str = CheckPostfix(w, "çu", 2)) != (w) ||
        (str = CheckPostfix(w, "ç"+QString(uh), 2)) != (w))
        return str;


    //"da"+QString(sh):
    if ((str = CheckPostfix(w, "da"+QString(sh), 3)) != (w))
        return str;


    //"l"+QString(eh)+"r" & "lar":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"r", 2)) != (w) ||
        (str = CheckPostfix(w, "lar", 2)) != (w))
        return str;


    //"l"+QString(eh)+"ri" & "lari":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"ri", 2)) != (w) ||
        (str = CheckPostfix(w, "lar"+QString(ih), 2)) != (w))
        return str;


    //"ligi/4":
    if ((str = CheckPostfix(w, "ligi", 2)) != (w) ||
        (str = CheckPostfix(w, "lu"+QString(gh)+"u", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(ih)+QString(gh)+QString(ih), 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(uh)+"g"+QString(uh), 2)) != (w))
        return str;


    //"ligin?/4":
    if ((str = CheckPostfix(w, "ligin"+QString(eh), 2)) != (w) ||
        (str = CheckPostfix(w, "lu"+QString(gh)+"una", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(ih)+QString(gh)+QString(ih)+"na", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(uh)+"g"+QString(uh)+"n"+QString(eh), 2)) != (w))
        return str;


    //"ligini/4":
    if ((str = CheckPostfix(w, "ligini", 2)) != (w) ||
        (str = CheckPostfix(w, "lu"+QString(gh)+"unu", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(ih)+QString(gh)+QString(ih)+"n"+QString(ih), 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(uh)+"g"+QString(uh)+"n"+QString(uh), 2)) != (w))
        return str;


    //"l?r?" & "lara":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"r"+QString(eh), 2)) != (w) ||
        (str = CheckPostfix(w, "lara", 2)) != (w))
        return str;


    //"d?ki" & "daki":
    if ((str = CheckPostfix(w, "d"+QString(eh)+"ki", 2)) != (w) ||
        (str = CheckPostfix(w, "dak"+QString(ih), 2)) != (w))
        return str;


    //"?l?s" & "?las":
    if (w.length() > 3 &&
        ((IsFrontVowel(w[w.length() - 4]) && (str = CheckPostfix(w, "l"+QString(eh)+QString(sh), 2)) != w) ||
        (IsBackVowel(w[w.length() - 4]) && (str = CheckPostfix(w, "la"+QString(sh), 2)) != (w))))
            return str;
    if (w.length() > 4 &&
        ((IsFrontVowel(w[w.length() - 5]) && (str = CheckPostfix(w, "l"+QString(eh)+QString(sh), 2)) != w) ||
         (IsBackVowel(w[w.length() - 5]) && (str = CheckPostfix(w, "la"+QString(sh), 2)) != (w))))
            return str;
    if (w.length() > 5 &&
        ((IsFrontVowel(w[w.length() - 6]) && (str = CheckPostfix(w, "l"+QString(eh)+QString(sh), 2)) != w) ||
         (IsBackVowel(w[w.length() - 6]) && (str = CheckPostfix(w, "la"+QString(sh), 2)) != (w))))
            return str;


    //"r?k" & "raq":
    if ((str = CheckPostfix(w, "r"+QString(eh)+"k", 2)) != (w) ||
        (str = CheckPostfix(w, "raq", 2)) != (w))
        return str;


    //"zad?":
    if ((str = CheckPostfix(w, "zad"+QString(eh), 2)) != (w))
        return str;


    //"l?n?" & "lana":
    if ((str = CheckPostfix(w, "l"+QString(eh)+"n"+QString(eh), 2)) != (w) ||
        (str = CheckPostfix(w, "lana", 2)) != (w))
        return str;


    //"?sini/8":
    if (w.length() > 4 &&
        ((w[w.length() - 5] == eh && (str = CheckPostfix(w, "sini", 3)) != (w)) ||
        (w[w.length() - 5] == 'a' && (str = CheckPostfix(w, "s"+QString(ih)+"n"+QString(ih), 1)) != (w)) ||
        (w[w.length() - 5] == 'u' && (str = CheckPostfix(w, "sunu", 1)) != (w)) ||
        (w[w.length() - 5] == 'i' && (str = CheckPostfix(w, "sini", 2)) != (w)) ||
        (w[w.length() - 5] == ih && (str = CheckPostfix(w, "s"+QString(ih)+"n"+QString(ih), 2)) != (w)) ||
        (w[w.length() - 5] == uh && (str = CheckPostfix(w, "s"+QString(uh)+"n"+QString(uh), 1)) != (w)) ||
        (w[w.length() - 5] == oh && (str = CheckPostfix(w, "s"+QString(uh)+"n"+QString(uh), 1)) != (w)) ||
        (w[w.length() - 5] == 'o' && (str = CheckPostfix(w, "sunu", 1)) != (w))))
        return str;


    //"?sin/8":
    if (w.length() > 3 &&
        ((w[w.length() - 4] == eh && (str = CheckPostfix(w, "sin", 3)) != (w)) ||
        (w[w.length() - 4] == 'a' && (str = CheckPostfix(w, "s"+QString(ih)+"n", 1)) != (w)) ||
        (w[w.length() - 4] == 'u' && (str = CheckPostfix(w, "sun", 1)) != (w)) ||
        (w[w.length() - 4] == 'i' && (str = CheckPostfix(w, "sin", 2)) != (w)) ||
        (w[w.length() - 4] == ih && (str = CheckPostfix(w, "s"+QString(ih)+"n", 2)) != (w)) ||
        (w[w.length() - 4] == uh && (str = CheckPostfix(w, "s"+QString(uh)+"n", 1)) != (w)) ||
        (w[w.length() - 4] == oh && (str = CheckPostfix(w, "s"+QString(uh)+"n", 1)) != (w)) ||
        (w[w.length() - 4] == 'o' && (str = CheckPostfix(w, "sun", 1)) != (w))))
        return str;


    //"ini/4":
    if ((str = CheckPostfix(w, "ini", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"n"+QString(ih), 1)) != (w) ||
        (str = CheckPostfix(w, "unu", 1)) != (w) ||
        (str = CheckPostfix(w, QString(uh)+"n"+QString(uh), 1)) != (w))
        return str;


    //"?si/8":
    if (w.length() > 2 &&
        ((w[w.length() - 3] == eh && (str = CheckPostfix(w, "si", 3)) != (w)) ||
        (w[w.length() - 3] == 'a' && (str = CheckPostfix(w, "s"+QString(ih), 1)) != (w)) ||
        (w[w.length() - 3] == 'u' && (str = CheckPostfix(w, "su", 1)) != (w)) ||
        (w[w.length() - 3] == 'i' && (str = CheckPostfix(w, "si", 2)) != (w)) ||
        (w[w.length() - 3] == ih && (str = CheckPostfix(w, "s"+QString(ih), 2)) != (w)) ||
        (w[w.length() - 3] == uh && (str = CheckPostfix(w, "s"+QString(uh), 1)) != (w)) ||
        (w[w.length() - 3] == oh && (str = CheckPostfix(w, "s"+QString(uh), 1)) != (w)) ||
        (w[w.length() - 3] == 'o' && (str = CheckPostfix(w, "su", 1)) != (w))))
        return str;


    //Milki z?mirl?r:
    if ((str = CheckPostfix(w, "im", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"m", 1)) != (w) ||
        (str = CheckPostfix(w, "um", 1)) != (w) ||
        (str = CheckPostfix(w, QString(uh)+"m", 1)) != (w) ||

        (w.length() > 3 && w[w.length() - 3] != 'n' && (str = CheckPostfix(w, "in", 1)) != (w)) ||
        (w.length() > 3 && w[w.length() - 3] != 'n' && (str = CheckPostfix(w, QString(ih)+"n", 1)) != (w)) ||
        (w.length() > 3 && w[w.length() - 3] != 'n' && (str = CheckPostfix(w, "un", 1)) != (w)) ||
        (w.length() > 3 && w[w.length() - 3] != 'n' && (str = CheckPostfix(w, QString(uh)+"n", 1)) != (w)) ||

        (str = CheckPostfix(w, "imiz", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"m"+QString(ih)+"z", 1)) != (w) ||
        (str = CheckPostfix(w, "umuz", 1)) != (w) ||
        (str = CheckPostfix(w, QString(uh)+"m"+QString(uh)+"z", 1)) != (w) ||

        (str = CheckPostfix(w, "iniz", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih)+"n"+QString(ih)+"z", 1)) != (w) ||
        (str = CheckPostfix(w, "unuz", 1)) != (w) ||
        (str = CheckPostfix(w, QString(uh)+"n"+QString(uh)+"z", 1)) != (w))
        return str;


    //"?nin/8":
    if (w.length() > 3 &&
        ((w[w.length() - 4] == eh && (str = CheckPostfix(w, "nin", 3)) != (w)) ||
        (w[w.length() - 4] == 'a' && (str = CheckPostfix(w, "n"+QString(ih)+"n", 1)) != (w)) ||
        (w[w.length() - 4] == 'u' && (str = CheckPostfix(w, "nun", 1)) != (w)) ||
        (w[w.length() - 4] == 'i' && (str = CheckPostfix(w, "nin", 2)) != (w)) ||
        (w[w.length() - 4] == ih && (str = CheckPostfix(w, "n"+QString(ih)+"n", 2)) != (w)) ||
        (w[w.length() - 4] == uh && (str = CheckPostfix(w, "n"+QString(uh)+"n", 1)) != (w)) ||
        (w[w.length() - 4] == oh && (str = CheckPostfix(w, "n"+QString(uh)+"n", 1)) != (w)) ||
        (w[w.length() - 4] == 'o' && (str = CheckPostfix(w, "nun", 1)) != (w))))
        return str;


    //"?yib/8":
    if (w.length() > 3 &&
        ((w[w.length() - 4] == eh && (str = CheckPostfix(w, "yib", 3)) != (w)) ||
        (w[w.length() - 4] == 'a' && (str = CheckPostfix(w, "y"+QString(ih)+"b", 1)) != (w)) ||
        (w[w.length() - 4] == 'u' && (str = CheckPostfix(w, "yub", 1)) != (w)) ||
        (w[w.length() - 4] == 'i' && (str = CheckPostfix(w, "yib", 1)) != (w)) ||
        (w[w.length() - 4] == ih && (str = CheckPostfix(w, "y"+QString(ih)+"b", 1)) != (w)) ||
        (w[w.length() - 4] == uh && (str = CheckPostfix(w, "y"+QString(uh)+"b", 1)) != (w)) ||
        (w[w.length() - 4] == oh && (str = CheckPostfix(w, "y"+QString(uh)+"b", 1)) != (w)) ||
        (w[w.length() - 4] == 'o' && (str = CheckPostfix(w, "yub", 1)) != (w))))
        return str;


    //"?miyib/8":
    if (w.length() > 5 &&
        ((w[w.length() - 6] == eh && (str = CheckPostfix(w, "m"+QString(eh)+"yib", 3)) != (w)) ||
        (w[w.length() - 6] == 'a' && (str = CheckPostfix(w, "may"+QString(ih)+"b", 1)) != (w)) ||
        (w[w.length() - 6] == 'u' && (str = CheckPostfix(w, "muyub", 1)) != (w)) ||
        (w[w.length() - 6] == 'i' && (str = CheckPostfix(w, "miyib", 1)) != (w)) ||
        (w[w.length() - 6] == ih && (str = CheckPostfix(w, "m"+QString(ih)+"y"+QString(ih)+"b", 1)) != (w)) ||
        (w[w.length() - 6] == uh && (str = CheckPostfix(w, "m"+QString(uh)+"y"+QString(uh)+"b", 1)) != (w)) ||
        (w[w.length() - 6] == oh && (str = CheckPostfix(w, "m"+QString(uh)+"y"+QString(uh)+"b", 1)) != (w)) ||
        (w[w.length() - 6] == 'o' && (str = CheckPostfix(w, "muyub", 1)) != (w))))
        return str;


    //"dir/4":
    if ((str = CheckPostfix(w, "dir", 2)) != (w) ||
        (str = CheckPostfix(w, "d"+QString(ih)+"r", 2)) != (w) ||
        (str = CheckPostfix(w, "dur", 2)) != (w) ||
        (str = CheckPostfix(w, "d"+QString(uh)+"r", 2)) != (w))
        return str;
    //"di/4":
    if ((str = CheckPostfix(w, "di", 3)) != (w) ||
        (str = CheckPostfix(w, "d"+QString(ih), 3)) != (w) ||
        (str = CheckPostfix(w, "du", 3)) != (w) ||
        (str = CheckPostfix(w, "d"+QString(uh), 3)) != (w))
        return str;


    //"siz/4":
    if ((str = CheckPostfix(w, "siz", 2)) != (w) ||
        (str = CheckPostfix(w, "s"+QString(ih)+"z", 2)) != (w) ||
        (str = CheckPostfix(w, "suz", 2)) != (w) ||
        (str = CheckPostfix(w, "s"+QString(uh)+"z", 2)) != (w))
        return str;


    //"miz/4":
    if ((str = CheckPostfix(w, "miz", 3)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(ih)+"z", 3)) != (w) ||
        (str = CheckPostfix(w, "muz", 3)) != (w) ||
        (str = CheckPostfix(w, "m"+QString(uh)+"z", 3)) != (w))
        return str;


    //"niz/4":
    if ((str = CheckPostfix(w, "niz", 3)) != (w) ||
        (str = CheckPostfix(w, "n"+QString(ih)+"z", 3)) != (w) ||
        (str = CheckPostfix(w, "nuz", 3)) != (w) ||
        (str = CheckPostfix(w, "n"+QString(uh)+"z", 3)) != (w))
        return str;


    //"?y?" & "?ya":
    if (w.length() > 2 &&
        (IsFrontVowel(w[w.length() - 3]) && (str = CheckPostfix(w, "y"+QString(eh), 3)) != (w) ||
         IsBackVowel (w[w.length() - 3]) && (str = CheckPostfix(w, "ya", 1)) != (w)))
        return str;


    //"c?" & "ca":
    if ((str = CheckPostfix(w, "c"+QString(eh), 3)) != (w) ||
        (str = CheckPostfix(w, "ca", 3)) != (w))
        return str;


    //"c?k" & "caq":
    if ((w.length() > 3 && IsFrontVowel(w[w.length() - 4]) && (str = CheckPostfix(w, "c"+QString(eh)+"k", 2)) != (w)) ||
        (w.length() > 3 && IsBackVowel (w[w.length() - 4]) && (str = CheckPostfix(w, "caq", 2)) != (w)))
        return str;


    //"lik" & "liq":
    if ((str = CheckPostfix(w, "lik", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(ih)+"q", 2)) != (w))
        return str;


    //"liki" & ""ligi:
    if ((str = CheckPostfix(w, "liki", 2)) != (w) ||
        (str = CheckPostfix(w, "liyi", 2)) != (w) ||
        (str = CheckPostfix(w, "l"+QString(ih)+QString(gh)+QString(ih), 2)) != (w))
        return str;


    //"d?n" & "dan":
    if ((str = CheckPostfix(w, "d"+QString(eh)+"n", 2)) != (w) ||
        (str = CheckPostfix(w, "dan", 2)) != (w))
        return str;


    //"m?k" & "maq":
    if ((str = CheckPostfix(w, "m"+QString(eh)+"k", 4)) != (w) ||
        (str = CheckPostfix(w, "maq", 4)) != (w))
        return str;


    //"d?" & "da":
    if ((str = CheckPostfix(w, "d"+QString(eh), 3)) != (w) ||
        (str = CheckPostfix(w, "da", 1)) != (w))
        return str;


    //"s?" & "sa":
    if ((str = CheckPostfix(w, "s"+QString(eh), 3)) != (w) ||
        (str = CheckPostfix(w, "sa", 1)) != (w))
        return str;


    //"m" & "n":
    if (w.length() > 1 && IsSesli(w[w.length() - 2]) &&
        ((str = CheckPostfix(w, "m", 4)) != (w) ||
        (str = CheckPostfix(w, "n", 4)) != (w)))
        return str;


    //"i/6": (must be the last postfix checked!)
    if ((str = CheckPostfix(w, "i", 1)) != (w) ||
        (str = CheckPostfix(w, QString(ih), 1)) != (w) ||
        (str = CheckPostfix(w, "u", 1)) != (w) ||
        (str = CheckPostfix(w, QString(uh), 1)) != (w) ||
        (str = CheckPostfix(w, "a", 1)) != (w) ||
        (str = CheckPostfix(w, eh, 1)) != (w))
        return str;



    return str;
}


QString L2AConversion::ChangePrefixes(const QString& w)
        {
            if (w.isNull() || w.isEmpty())
                return "";

            QString str(w);
            if ((w.length() > 5) && w.mid(0, 4) == ("yeni"))
                return (QString("")+QChar('\xcc', '\x06')+QChar('\x26', '\x06')+QChar('\x46', '\x06')+QChar('\xcc', '\x06')+QString(vs) + ConvertWord(w.mid(4, w.length() - 4), true));
            if ((w.length() > 5) && w.mid(0, 4) == ("anti"))
                return (QString("")+QChar('\x22', '\x06')+QChar('\x46', '\x06')+QChar('\x2a', '\x06')+QChar('\xcc', '\x06')+QString(vs) + ConvertWord(w.mid(4, w.length() - 4), true));
            if ((w.length() > 5) && w.mid(0, 4) == ("q"+QString(eh)+"r"+QString(eh)))
                return (QString("")+QChar('\x42', '\x06')+QChar('\x31', '\x06')+QChar('\x47', '\x06')+QString(vs) + ConvertWord(w.mid(4, w.length() - 4), true));
            if ((w.length() > 5) && w.mid(0, 4) == ("t"+QString(eh)+"z"+QString(eh)))
                str = QString("")+QChar('\x2a', '\x06')+QChar('\x32', '\x06')+QChar('\x47', '\x06')+QString(vs) + ConvertWord(w.mid(4, w.length() - 4), true);
            return str;
        }



QString L2AConversion::CheckPostfix(const QString& w, const QString& pff, int sp)
{
    QString pf(pff);
    QString str(w);
    int length = w.length();
    int num2 = pf.length();
    if ((length <= (num2 + 2)) || w.mid(length - num2, num2) != (pf))
        return str;


    str = ConvertWord(w.mid(0, length - num2), true);
    switch (sp)
    {
        case 1:
            //Nothing to do!
            break;

        case 2:
            if (IsSonrayaYapisan(w[(length - num2) - 1]))
                str = str + vs;
            break;

        case 3:
            if (w[(length - num2) - 1] == eh)
                str = str + vs;
            break;

        case 4:
            if (w[(length - num2) - 1] == eh)
                str = str.mid(0, str.length() - 1);
            break;
    }
    QChar c = pf[0];
    if (c == uh || c == 'u')
    {
        str = str + QChar('\x48', '\x06');
        pf = pf.mid(1, --num2);
    }
    else if (c == 'i' || c == ih)
    {
        str = str + QChar('\xcc', '\x06');
        pf = pf.mid(1, --num2);
    }
    else if (c == eh)
    {
        str = str + QChar('\x47', '\x06');
        pf = pf.mid(1, --num2);
    }
    else if (c == 'a')
    {
        str = str + QChar('\x27', '\x06');
        pf = pf.mid(1, --num2);
    }

    return (str + ConvertWord(pf, false));
}


void L2AConversion::PreprocessText()
{
    //Changing "dr." to "dr "
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
    }
}


QString L2AConversion::Convert(QProgressDialog* prg)
{
    //Load wiki mode:
	bool wikiMode = Settings::GetInstance(this->parent())->GetWikiMode();

    //These variables are used in wiki mode:
    int doubleBracket=0;
    bool openBracketSeen = false;
    bool closeBracketSeen = false;

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
        if (!wikiMode || (doubleBracket == 0 || !IsThereColonBeforeDoubleCloseBrackets(i)))
            strResult += ConvertWord(word, true);
        else
            strResult += word;


        while ((i < length) && !IsCharAInWordChar(strSource[i]))
        {
            QChar curChar = strSource[i];
            //Wikimode:
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
            //******************* End counting double brakcets: *********************


            //Converting characters:
            QChar ch = GetSpecialChar(curChar);
            if (ch != ' ')
                strResult = strResult + QString(ch);
            else
                strResult = strResult + QString(curChar);
            i++;
        }
    }
    return GetResult();
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


QString L2AConversion::ConvertHtml()
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
}


QChar L2AConversion::ConvertSessizChar(QChar c)
{
    if (c == 'b')
        return QChar('\x28', '\x06');

    else if (c == 'c')
        return QChar('\x2c', '\x06');

    else if (c == 'd')
        return QChar('\x2f', '\x06');

    else if (c == 'f')
        return QChar('\x41', '\x06');

    else if (c == 'g')
        return QChar('\xaf', '\x06');

    else if (c == 'h')
        return QChar('\x47', '\x06');

    else if (c == 'j')
        return QChar('\x98', '\x06');

    else if (c == 'k')
        return QChar('\xa9', '\x06');

    else if (c == 'l')
        return QChar('\x44', '\x06');

    else if (c == 'm')
        return QChar('\x45', '\x06');

    else if (c == 'n')
        return QChar('\x46', '\x06');

    else if (c == 'p')
        return QChar('\x7e', '\x06');

    else if (c == 'q')
        return QChar('\x42', '\x06');

    else if (c == 'r')
        return QChar('\x31', '\x06');

    else if (c == 's')
        return QChar('\x33', '\x06');

    else if (c == 't')
        return QChar('\x2a', '\x06');

    else if (c == 'v')
        return QChar('\x48', '\x06');

    else if (c == 'x')
        return QChar('\x2e', '\x06');

    else if (c == 'y')
        return QChar('\xcc', '\x06');

    else if (c == 'z')
        return QChar('\x32', '\x06');

    else if (c == '\'')
        return QChar('\x39', '\x06');

    else if (c == ch)
        return QChar('\x86', '\x06');

    else if (c == gh)
        return QChar('\x3a', '\x06');

    else if (c == sh)
        return QChar('\x34', '\x06');

    else
        return 'a';
}

QString L2AConversion::ConvertWord(const QString& wo, bool isRecursive)
{
    QString word(wo);
    if (word.isNull() || word.isEmpty())
        return "";

    if (IsNonConvertableWord(word))
        return word;


    word = word.replace(Ih, 'i', Qt::CaseSensitive);
    word = word.toLower();
    QString str("");
    str = GetWordFromDictionary(word);
    if (str == "")
    {
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
        if (isRecursive)
        {
            word = ChangePostfixes(word);
            word = ChangePrefixes(word);
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
            QChar c = word[i];
            //QString chr = "a";
            if (i == 0)
            {
                if (c == eh || c == QChar('\xd9', '\x04'))
                {
                    str = str + QChar('\x27', '\x06');
                    continue;
                }

                else if (c == 'a')
                {
                    str += QString(QChar('\x22', '\x06'));
                    continue;
                }

                else if (c == 'o' || c == 'u' || c == uh)
                {
                    str = str + QChar('\x27', '\x06')+ QChar('\x48', '\x06');
                    continue;
                }

                else if (c == oh)
                {
                    str = str + QChar('\x27', '\x06')+QChar('\x24', '\x06');
                    continue;
                }

                else if (c == 'e')
                {
                    str = str + QChar('\x27', '\x06')+QChar('\x26', '\x06');
                    continue;
                }

                else if (c == 'i' || c == ih)
                {
                    str = str + QChar('\x27', '\x06')+QChar('\xcc', '\x06');
                    continue;
                }
            }
            else if ((i == length - 1) && (c == eh || c == QChar('\xd9', '\x04')))
            {
                str = str + QChar('\x47', '\x06');
                continue;
                break;
            }
            else
            {
                if (c == eh || c == QChar('\xd9', '\x04') || c == '\'')
                    continue;

                else if (c == 'a')
                {
                    str = str + QChar('\x27', '\x06');
                    continue;
                }

                else if (c == 'o' || c == 'u' || c == uh)
                {
                    str = str + QChar('\x48', '\x06');
                    continue;
                }

                else if (c == oh)
                {
                    str = str + QChar('\x24', '\x06');
                    continue;
                }

                else if (c == 'e')
                {
                    str = str + QChar('\x26', '\x06');
                    continue;
                }

                else if (c == 'i' || c == ih)
                {
                    str = str + QChar('\xcc', '\x06');
                    continue;
                }
            }


            if (IsSessiz(c))
            {
                str += QString(ConvertSessizChar(c));
                continue;
            }
            else
            {
                str += QString(c);
                continue;
            }
        }
    }
    return str;
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

QString L2AConversion::GetSpecialWord(const QString& w)
{
    return "";
}

QString L2AConversion::GetWord(int i, QChar delim)
{

}

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

QString L2AConversion::GetWordFromDictionary(const QString& w)
{
    QString word(w);
    word = "[" + word + "]";
    if (!AL2AA.contains(word))
    {
        return "";
    }
    int index = AL2AA.indexOf(word);
    while (AL2AA[index] != '=')
    {
        index++;
    }
    index++;
    int num2 = index;
    QString str = "";
    while (((num2 < AL2AA.length()) && (AL2AA[num2] != '\r')) && (AL2AA[num2] != '\n'))
    {
        str = str + QString(AL2AA[num2]);
        num2++;
    }
    return str;
}

bool L2AConversion::IsBackVowel(QChar c)
{
    return (c == 'a' || c == 'u' || c == 'o' || c == ih);
}

bool L2AConversion::IsCharAInWordChar(QChar c)
{
    return !(c == ' ' || c == '\n'|| c == '\t'|| c == '\r'||
             c == '?' || c == '.' || c == '!' || c == '(' ||
             c == ')' || c == '[' || c == ']' || c == '{' ||
             c == '}' || c == '"' || c == '-' || c == '=' ||
             c == ',' || c == ':' || c == ';' || c == '<' ||
             c == '>' || c == '|' ||
             c == QChar('\x1c', '\x20') || c == QChar('\x1d', '\x20'));
}

bool L2AConversion::IsFrontVowel(QChar c)
{
    return (c == eh || c == 'e' || c == uh || c == oh || c == 'i');
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

bool L2AConversion::IsSesli(QChar c)
{
    return (c == 'a' || c == eh || c == uh || c == 'o'
         || c == oh || c == 'u' || c == 'e' || c == 'i');
}

bool L2AConversion::IsSessiz(QChar c)
{
    return (c == 'z' || c == 'b' || c == 'c' || c == 'd'
         || c == 'f' || c == 'g' || c == 'h' || c == 'j'
         || c == 'k' || c == 'l' || c == 'm' || c == 'n'
         || c == 'p' || c == 'q' || c == 'r' || c == 's'
         || c == 't' || c == 'v' || c == 'x' || c == 'y'
         || c == sh || c == ch || c == gh);
}

bool L2AConversion::IsSonrayaYapisan(QChar c)
{
    return !(c == 'd' || c == 'o' || c == 'z' || c == 'r'
          || c == 'j' || c == oh || c == 'u' || c == uh);
}

void L2AConversion::OpenDicts()
{
	//QString path = QDir::currentPath();
	QString path = QCoreApplication::applicationDirPath();
    path = path + QDir::separator() + "dicts" + QDir::separator();
    QFile file(path + "dict_AzL2AzA.dat");
    //QMessageBox::warning(NULL, "", QDir::currentPath());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        AL2AA = QString::fromUtf8(file.readAll());
    }
    else
    {
        QMessageBox::warning(NULL, tr("Dictionary"), tr("File not found!\nWorking in non dictionary mode!", "Error"));
        AL2AA = "";
        return;
    }

    QFile file2(path + "dict_AzL2AzA_user.dat");
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        AL2AA += QString::fromUtf8(file2.readAll());
    }
    else
        return;
}

void L2AConversion::SetOriginalText(const QString& str)
{
    strSource = str;
    strResult = "";
}













