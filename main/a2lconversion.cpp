#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressDialog>
#include <QVariant>

#include "a2lconversion.h"
#include "dbservice.h"


A2LConversion::A2LConversion(QObject* parent)
    : Convertor(parent)
{
    reloadResources();
}


/*void A2LConversion::reloadResources()
{
    loadChars();
    loadWords();
    //loadSolidWords();
    //loadPrefixes();
    //loadPostfixes();
    loadSpecialChars();
}*/


QString A2LConversion::getTablesPostfix()
{
    return "_a2l";
}


bool A2LConversion::canAddWords()
{
    return true;
}


QStringList A2LConversion::getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record)
{
    QStringList tuple;
    tuple << query.value(record.indexOf("start")).toString()
          << query.value(record.indexOf("mid")).toString()
          << query.value(record.indexOf("end")).toString()
          << query.value(record.indexOf("start_voc")).toString()
          << query.value(record.indexOf("mid_voc")).toString()
          << query.value(record.indexOf("end_voc")).toString();

    return tuple;
}


Qt::LayoutDirection A2LConversion::getSourceLayoutDirection()
{
    return Qt::RightToLeft;
}


Qt::LayoutDirection A2LConversion::getDestinationLayoutDirection()
{
    return Qt::LeftToRight;
}


void A2LConversion::setOriginalText(const QString &text)
{
    Convertor::setOriginalText(text);
    this->strResult = "";
}


void A2LConversion::replaceSpecialChars(QString &/*text*/)
{
}


void A2LConversion::ChangeAlternativeForms()
{
    strSource = strSource.replace(QChar('\x4a', '\x06'), QChar('\xcc', '\x06'));
    strSource = strSource.replace(QChar('\x43', '\x06'), QChar('\xa9', '\x06'));
    strSource = strSource.replace(QChar('\x2b', '\x20'), QChar('\x0c', '\x20'));
    strSource = strSource.replace(QChar('\x4e', '\x06'), QChar('\x59', '\x02'));
    strSource = strSource.replace(QChar('\x4f', '\x06'), 'o');
    strSource = strSource.replace(QChar('\x50', '\x06'), 'e');
    strSource = strSource.replace("\u0649", "\u06cc");
    strSource = strSource.replace("\u0640", "");    //Ignore '-'
}


QString A2LConversion::ChangePostfixes(const QString& w)
{
    if (w.isNull() || w.isEmpty())
        return "";

    QString str(w);

    if ((str = CheckPostfix(w, "\u067e\u0631\u0633\u062a", "p\u0259r\u0259st")) != w ||
        (str = CheckPostfix(w, "\u0628\u0627\u0631\u0627\u0646", "baran")) != w ||
        (str = CheckPostfix(w, "\u0634\u0648\u0646\u0627\u0633", "\u015f\u00fcnas")) != w ||
        (str = CheckPostfix(w, "\u0634\u0646\u0627\u0633", "\u015f\u00fcnas")) != w ||
        (str = CheckPostfix(w, "\u062e\u0627\u0646\u0627", "xana")) != w ||
        (str = CheckPostfix(w, "\u062e\u0627\u0646\u0647", "xana")) != w ||
        (str = CheckPostfix(w, "\u067e\u0631\u0648\u0631", "p\u0259rv\u0259r")) != w ||
        (str = CheckPostfix(w, "\u0637\u0644\u0628", "t\u0259l\u0259b")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0633\u0626\u0648\u0631", "sev\u0259r")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0631\u06cc\u0645\u062f\u0646", "l\u0259rimd\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc\u0645\u062f\u0627\u0646", "lar\u0131mdan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0631\u06cc\u0648\u062f\u0646", "l\u0259rivd\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc\u0648\u062f\u0627\u0646", "lar\u0131vdan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0631\u06cc\u0646\u062f\u0646", "l\u0259rind\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc\u0646\u062f\u0627\u0646", "lar\u0131ndan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0631\u06cc\u0645\u06cc\u0632\u062f\u0646", "l\u0259rimizd\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc\u0645\u06cc\u0632\u062f\u0627\u0646", "lar\u0131m\u0131zdan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0631\u06cc\u0646\u06cc\u0632\u062f\u0646", "l\u0259rinizd\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc\u0646\u06cc\u0632\u062f\u0627\u0646", "lar\u0131n\u0131zdan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0631\u06cc\u0632\u062f\u0646", "l\u0259rizd\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc\u0632\u062f\u0627\u0646", "lar\u0131zdan")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0646\u06cc\u0631\u0645", "l\u0259nir\u0259m")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u06cc\u0631\u0627\u0645", "lan\u0131ram")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u06cc\u0631\u0633\u0646", "l\u0259nirs\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u06cc\u0631\u0633\u0627\u0646", "lan\u0131rsan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u06cc\u0631", "l\u0259nir")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u06cc\u0631", "lan\u0131r")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u06cc\u0631\u06cc\u06a9", "l\u0259nirik")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u06cc\u0631\u06cc\u0642", "lan\u0131r\u0131q")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u06cc\u0631\u0633\u06cc\u0646\u06cc\u0632", "l\u0259nirsiniz")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u06cc\u0631\u0633\u06cc\u0646\u06cc\u0632", "lan\u0131rs\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u06cc\u0631\u0633\u06cc\u0632", "l\u0259nirsiz")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u06cc\u0631\u0633\u06cc\u0632", "lan\u0131rs\u0131z")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0646\u0645\u06cc\u0631\u0645", "l\u0259nmir\u0259m")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0645\u06cc\u0631\u0627\u0645", "lanm\u0131ram")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u0645\u06cc\u0631\u0633\u0646", "l\u0259nmirs\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0645\u06cc\u0631\u0633\u0627\u0646", "lanm\u0131rsan")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u0645\u06cc\u0631", "l\u0259nmir")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0645\u06cc\u0631", "lanm\u0131r")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u0645\u06cc\u0631\u06cc\u06a9", "l\u0259nmirik")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0645\u06cc\u0631\u06cc\u0642", "lanm\u0131r\u0131q")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u0645\u06cc\u0631\u0633\u06cc\u0646\u06cc\u0632", "l\u0259nmirsiniz")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0645\u06cc\u0631\u0633\u06cc\u0646\u06cc\u0632", "lanm\u0131rs\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0644\u0646\u0645\u06cc\u0631\u0633\u06cc\u0632", "l\u0259nmirsiz")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0645\u06cc\u0631\u0633\u06cc\u0632", "lanm\u0131rs\u0131z")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u06cc\u0631\u0645", "ir\u0259m")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u0633\u0646", "irs\u0259n")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u06cc\u06a9", "irik")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u0633\u06cc\u0646\u06cc\u0632", "irsiniz", "\u0131rs\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u0633\u06cc\u0632", "irsiz", "\u0131rs\u0131z")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u0627\u0645", "\u0131ram")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u0633\u0627\u0646", "\u0131rsan")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u06cc\u0642", "\u0131r\u0131q")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0645\u06cc\u0631\u0645", "mir\u0259m")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u0633\u0646", "mirs\u0259n")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u06cc\u06a9", "mirik")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u0633\u06cc\u0646\u06cc\u0632", "mirsiniz", "m\u0131rs\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u0633\u06cc\u0632", "mirsiz", "m\u0131rs\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u0627\u0645", "m\u0131ram")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u0633\u0627\u0646", "m\u0131rsan")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u06cc\u0642", "m\u0131r\u0131q")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc\u0645", "irdim", "\u0131rd\u0131m")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc\u0646", "irdin", "\u0131rd\u0131n")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc", "irdi", "\u0131rd\u0131")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc\u06a9", "irdik")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc\u0646\u06cc\u0632", "irdiniz", "\u0131rd\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc\u0632", "irdiz", "\u0131rd\u0131z")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0631\u062f\u06cc\u0642", "\u0131rd\u0131q")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc\u0645", "mirdim", "\u0131rd\u0131m")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc\u0646", "mirdin", "\u0131rd\u0131n")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc", "mirdi", "\u0131rd\u0131")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc\u06a9", "mirdik")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc\u0646\u06cc\u0632", "mirdiniz", "\u0131rd\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc\u0632", "mirdiz", "\u0131rd\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0631\u062f\u06cc\u0642", "m\u0131rd\u0131q")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u0645", "mi\u015fdim", "m\u0131\u015fd\u0131m")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u0646", "mi\u015fdin", "m\u0131\u015fd\u0131n")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc", "mi\u015fdi", "m\u0131\u015fd\u0131")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u06a9", "mi\u015fdik")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u0646\u06cc\u0632", "mi\u015fdiniz", "m\u0131\u015fd\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u0632", "mi\u015fdiz", "m\u0131\u015fd\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u0642", "m\u0131\u015fd\u0131q")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0645\u0645\u06cc\u0634\u062f\u06cc\u0645", "m\u0259mi\u015fdim")) != w ||
        (str = CheckPostfix(w, "\u0645\u0645\u06cc\u0634\u062f\u06cc\u0646", "m\u0259mi\u015fdin")) != w ||
        (str = CheckPostfix(w, "\u0645\u0645\u06cc\u0634\u062f\u06cc", "m\u0259mi\u015fdi")) != w ||
        (str = CheckPostfix(w, "\u0645\u0645\u06cc\u0634\u062f\u06cc\u06a9", "m\u0259mi\u015fdik")) != w ||
        (str = CheckPostfix(w, "\u0645\u0645\u06cc\u0634\u062f\u06cc\u0646\u06cc\u0632", "m\u0259mi\u015fdiniz")) != w ||
        (str = CheckPostfix(w, "\u0645\u0645\u06cc\u0634\u062f\u06cc\u0632", "m\u0259mi\u015fdiz", "m\u0131\u015fd\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u0627\u0645\u06cc\u0634\u062f\u06cc\u0645", "mam\u0131\u015fd\u0131m")) != w ||
        (str = CheckPostfix(w, "\u0645\u0627\u0645\u06cc\u0634\u062f\u06cc\u0646", "mam\u0131\u015fd\u0131n")) != w ||
        (str = CheckPostfix(w, "\u0645\u0627\u0645\u06cc\u0634\u062f\u06cc", "mam\u0131\u015fd\u0131")) != w ||
        (str = CheckPostfix(w, "\u0645\u0627\u0645\u06cc\u0634\u062f\u06cc\u0646\u06cc\u0632", "mam\u0131\u015fd\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u0627\u0645\u06cc\u0634\u062f\u06cc\u0632", "mam\u0131\u015fd\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u06cc\u0634\u062f\u06cc\u0642", "m\u0131\u015fd\u0131q")) != w)
        return str;

    if (GetWordFromDictionary(w.mid(0, w.length() - 1)) != "" &&
        ((str = CheckPostfix(w, "\u0647", "\u0259")) != w ||
         (str = CheckPostfix(w, "\u0627", "a")) != w ||
         (str = CheckPostfix(w, "\u06cc", "i", "\u0131")) != w ||
         (str = CheckPostfix(w, "\u0648", "\u00fc", "u")) != w))
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0648", "l\u00fc", "lu")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc", "li", "l\u0131")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0647", "l\u0259")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627", "la")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0686\u0648", "\u00e7\u00fc", "\u00e7u")) != w ||
        (str = CheckPostfix(w, "\u0686\u06cc", "\u00e7i", "\u00e7\u0131")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u062f\u0627\u0634", "da\u015f")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0631", "l\u0259r")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631", "lar")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0631\u06cc", "l\u0259ri")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u06cc", "lar\u0131")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0631\u0647", "l\u0259r\u0259")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0631\u0627", "lara")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u06cc\u06af\u06cc", "liyi")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u063a\u06cc", "l\u0131\u011f\u0131")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u06cc\u06cc", "liyi")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u06cc\u06af\u06cc\u0646\u06cc", "liyini")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u063a\u06cc\u0646\u06cc", "l\u0131\u011f\u0131n\u0131")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u06cc\u06cc\u0646\u06cc", "liyini")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u06cc\u06af\u06cc\u0646\u0647", "liyin\u0259")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u063a\u06cc\u0646\u0627", "l\u0131\u011f\u0131na")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u06cc\u06cc\u0646\u0647", "liyin\u0259")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u062f\u06a9\u06cc", "d\u0259ki")) != w ||
        (str = CheckPostfix(w, "\u062f\u0627\u06a9\u06cc", "dak\u0131")) != w ||
        (str = CheckPostfix(w, "\u062f\u0647?\u06a9\u06cc", "d\u0259ki")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0631\u06a9", "r\u0259k")) != w ||
        (str = CheckPostfix(w, "\u0631\u0627\u0642", "raq")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0632\u0627\u062f\u0647", "zad\u0259")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u0646\u0647", "l\u0259n\u0259")) != w ||
        (str = CheckPostfix(w, "\u0644\u0627\u0646\u0627", "lana")) != w)
        return str;

    if (w.length() > 4 &&
        ((w[w.length() - 5] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0633\u06cc\u0646\u06cc", "sini")) != w) ||
        (w[w.length() - 5] == QChar('\x27', '\x06') && (str = CheckPostfix(w, "\u0633\u06cc\u0646\u06cc", "s\u0131n\u0131")) != w) ||
        (w[w.length() - 5] == QChar('\x48', '\x06') && (str = CheckPostfix(w, "\u0633\u0648\u0646\u0648", "s\u00fcn\u00fc", "sunu")) != w) ||
        (w[w.length() - 5] == QChar('\xcc', '\x06') && (str = CheckPostfix(w, "\u0633\u06cc\u0646\u06cc", "sini", "s\u0131n\u0131")) != w) ||
        (w[w.length() - 5] == QChar('\x24', '\x06') && (str = CheckPostfix(w, "\u0633\u0648\u0646\u0648", "s\u00fcn\u00fc")) != w)))
        return str;

    if (w.length() > 3 &&
        ((w[w.length() - 4] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0633\u06cc\u0646", "sin")) != w) ||
        (w[w.length() - 4] == QChar('\x27', '\x06') && (str = CheckPostfix(w, "\u0633\u06cc\u0646", "s\u0131n")) != w) ||
        (w[w.length() - 4] == QChar('\x48', '\x06') && (str = CheckPostfix(w, "\u0633\u0648\u0646", "s\u00fcn", "sun")) != w) ||
        (w[w.length() - 4] == QChar('\xcc', '\x06') && (str = CheckPostfix(w, "\u0633\u06cc\u0646", "sin", "s\u0131n")) != w) ||
        (w[w.length() - 4] == QChar('\x24', '\x06') && (str = CheckPostfix(w, "\u0633\u0648\u0646", "s\u00fcn")) != w)))
        return str;

    if ((str = CheckPostfix(w, "\u06cc\u0646\u06cc", "ini", "\u0131n\u0131")) != w ||
        (str = CheckPostfix(w, "\u0648\u0646\u0648", "\u00fcn\u00fc", "unu")) != w)
        return str;

    if (w.length() > 2 &&
        ((w[w.length() - 3] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0633\u06cc", "si")) != w) ||
        (w[w.length() - 3] == QChar('\x27', '\x06') && (str = CheckPostfix(w, "\u0633\u06cc", "s\u0131")) != w) ||
        (w[w.length() - 3] == QChar('\x48', '\x06') && (str = CheckPostfix(w, "\u0633\u0648", "s\u00fc", "su")) != w) ||
        (w[w.length() - 3] == QChar('\xcc', '\x06') && (str = CheckPostfix(w, "\u0633\u06cc", "si", "s\u0131")) != w) ||
        (w[w.length() - 3] == QChar('\x24', '\x06') && (str = CheckPostfix(w, "\u0633\u0648", "s\u00fc")) != w)))
        return str;

    if ((str = CheckPostfix(w, "\u06a9\u0646", "k\u0259n")) != w)
        return str;

    if (w.length() > 3 && w[w.length() - 2] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0645", "m")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u06cc\u0646", "in", "\u0131n")) != w ||
        (str = CheckPostfix(w, "\u0648\u0646", "\u00fcn", "un")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0645\u06cc\u0632", "imiz", "\u0131m\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0648\u0645\u0648\u0632", "\u00fcm\u00fcz", "umuz")) != w ||
        (str = CheckPostfix(w, "\u06cc\u0646\u06cc\u0632", "iniz", "\u0131n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0648\u0646\u0648\u0632", "\u00fcn\u00fcz", "unuz")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u06cc\u0646", "in", "\u0131n")) != w && (GetWordFromDictionary(w.mid(0, w.length() - 2)) != ""))
        return str;

    if (w.length() > 3 &&
        ((w[w.length() - 4] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0646\u06cc\u0646", "nin")) != w) ||
        (w[w.length() - 4] == QChar('\x27', '\x06') && (str = CheckPostfix(w, "\u0646\u06cc\u0646", "n\u0131n")) != w) ||
        (w[w.length() - 4] == QChar('\x48', '\x06') && (str = CheckPostfix(w, "\u0646\u0648\u0646", "n\u00fcn", "nun")) != w) ||
        (w[w.length() - 4] == QChar('\xcc', '\x06') && (str = CheckPostfix(w, "\u0646\u06cc\u0646", "nin", "n\u0131n")) != w) ||
        (w[w.length() - 4] == QChar('\x24', '\x06') && (str = CheckPostfix(w, "\u0646\u0648\u0646", "n\u00fcn")) != w)))
        return str;

    if (w.length() > 3 &&
        ((w[w.length() - 4] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u06cc\u06cc\u0628", "yib")) != w) ||
        (w[w.length() - 4] == QChar('\x27', '\x06') && (str = CheckPostfix(w, "\u06cc\u06cc\u0628", "y\u0131b")) != w) ||
        (w[w.length() - 4] == QChar('\x48', '\x06') && (str = CheckPostfix(w, "\u06cc\u0648\u0628", "y\u00fcb", "yub")) != w) ||
        (w[w.length() - 4] == QChar('\xcc', '\x06') && (str = CheckPostfix(w, "\u06cc\u06cc\u0628", "yib", "y\u0131b")) != w) ||
        (w[w.length() - 4] == QChar('\x24', '\x06') && (str = CheckPostfix(w, "\u06cc\u0648\u0628", "y\u00fcb")) != w)))
        return str;

    if (w.length() > 5 &&
        ((w[w.length() - 6] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0645\u06cc\u06cc\u0628", "m\u0259yib")) != w) ||
        (w[w.length() - 6] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0645\u06cc\u06cc\u06cc\u0628", "m\u0259yib")) != w) ||
        (w[w.length() - 6] == QChar('\x59', '\x02') && (str = CheckPostfix(w, "\u0645\u0647?\u06cc\u06cc\u0628", "m\u0259yib")) != w) ||
        (w[w.length() - 6] == QChar('\x27', '\x06') && (str = CheckPostfix(w, "\u0645\u06cc\u06cc\u06cc\u0628", "m\u0131y\u0131b")) != w) ||
        (w[w.length() - 6] == QChar('\x48', '\x06') && (str = CheckPostfix(w, "\u0645\u0648\u06cc\u0648\u0628", "m\u00fcy\u00fcb", "muyub")) != w) ||
        (w[w.length() - 6] == QChar('\xcc', '\x06') && (str = CheckPostfix(w, "\u0645\u06cc\u06cc\u06cc\u0628", "miyib", "m\u0131y\u0131b")) != w) ||
        (w[w.length() - 6] == QChar('\x24', '\x06') && (str = CheckPostfix(w, "\u0645\u0648\u06cc\u0648\u0628", "m\u00fcy\u00fcb")) != w)))
        return str;

    if ((str = CheckPostfix(w, "\u062f\u06cc\u0631", "dir", "d\u0131r")) != w ||
        (str = CheckPostfix(w, "\u062f\u0648\u0631", "d\u00fcr", "dur")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0633\u06cc\u0632", "siz", "s\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0633\u0648\u0632", "s\u00fcz", "suz")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0645\u06cc\u0632", "miz", "m\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0645\u0648\u0632", "m\u00fcz", "muz")) != w ||
        (str = CheckPostfix(w, "\u0646\u06cc\u0632", "niz", "n\u0131z")) != w ||
        (str = CheckPostfix(w, "\u0646\u0648\u0632", "n\u00fcz", "nuz")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u062c\u0647", "c\u0259")) != w ||
        (str = CheckPostfix(w, "\u062c\u0627", "ca")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u062c\u06a9", "c\u0259k")) != w ||
        (str = CheckPostfix(w, "\u062c\u0627\u0642", "caq")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u06cc\u06a9", "lik")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u0642", "l\u0131q")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0644\u06cc\u06a9\u06cc", "liki")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u06cc\u06cc", "liyi")) != w ||
        (str = CheckPostfix(w, "\u0644\u06cc\u063a\u06cc", "l\u0131\u011f\u0131")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u062f\u0646", "d\u0259n")) != w ||
        (str = CheckPostfix(w, "\u062f\u0627\u0646", "dan")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0645\u06a9", "m\u0259k")) != w ||
        (str = CheckPostfix(w, "\u0645\u0627\u0642", "maq")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u062f\u0647", "d\u0259")) != w ||
        (str = CheckPostfix(w, "\u062f\u0627", "da")) != w)
        return str;

    if ((str = CheckPostfix(w, "\u0633\u0647", "s\u0259")) != w ||
        (str = CheckPostfix(w, "\u0633\u0627", "sa")) != w)
        return str;



    return str;
}

QString A2LConversion::CheckPostfix(const QString& w, const QString& pf, const QString& eq)
{
    QString str(w);
    int length = w.length();
    int num2 = pf.length();
    if ((length > (num2 + 2)) && w.mid(length - num2, num2) == pf)
    {
        int bf = ChooseBackOrFront(pf);
        str = ConvertWord(w.mid(0, length - num2), bf, false) + eq;
    }
    return str;
}

QString A2LConversion::CheckPostfix(const QString& w, const QString& pf, const QString& eq, const QString& eq2)
{
    QString str(w);
    int length = w.length();
    int num2 = pf.length();
    if (length <= (num2 + 2) || w.mid(length - num2, num2) != pf)
    {
        return str;
    }
    int bf = ChooseBackOrFront(pf);
    if (bf == 3)
        bf = ChooseBackOrFront(str);
    str = ConvertWord(w.mid(0, length - num2), bf, false);
    switch (ChooseBackOrFront(str))
    {
        case 1:
            return (str + eq);

        case 2:
            return (str + eq2);
    }
    return (str + eq2);
}

int A2LConversion::ChooseBackOrFront(const QString& w)
{
    if (w != "")
    {
        if (w.contains("\u0626") || w.contains("\u0624") || w.contains("e") || w.contains("\u00f6"))
            return 1;
        int length = w.length();
        for (int i = length - 1; i > 0; i--)
        {
            if (w[i] == QChar('\x27', '\x06') || w[i] == QChar('\x22', '\x06') || w[i] == 'a' || w[i] == QChar('\x31', '\x01') || w[i] == 'o' || w[i] == 'u')
                return 2;

            if ((w[i] == QChar('\x47', '\x06')) && IsEnd(w, i))
                return 1;

            if (w[i] == QChar('\x59', '\x02') || w[i] == 'e' || w[i] == 'i' || w[i] == QChar('\xfc', '\x00') || w[i] == QChar('\xf6', '\x00'))
                return 1;

            if (w[i] == QChar('\x26', '\x06') || w[i] == QChar('\x24', '\x06'))
                return 1;
        }
        if (w[0] == QChar('\x27', '\x06') && length > 1 && IsSessiz(w[1]))
            return 1;
    }
    return 3;
}

bool A2LConversion::ContainsBackVowel(const QString& w)
{
    if (w.contains("a") || w.contains("\u0622"))
        return true;

    int length = w.length();
    for (int i = 1; i < length; i++)
    {
        if ((w[i] == QChar('\x27', '\x06')) && (w[i - 1] != QChar('\x59', '\x02')))
            return true;
        if ((w[i] == QChar('\x26', '\x06')) || (w[i] == QChar('\x24', '\x06')))
            return false;
    }
    return false;
}

/*QString A2LConversion::convert(QString text, bool / *wikiMode* /)
{
    return convert(NULL, text);
}*/

QString A2LConversion::convert(QProgressDialog* prg, QString text)
{
	QString res;
    ChangeAlternativeForms();
    int length = text.length();
    int i = 0;
    while (i < length)
    {
        QString word = GetWord(i);
        i += word.length();
        QString w = ConvertWord(word, 0, false);

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

        w = IslahEt(w);
        res = res + w;
        while ((i < length) && !IsCharAInWordChar(text[i]))
        {
            QChar ch = GetSpecialChar(text[i]);
            if (ch != ' ')
                res += QChar(ch);
            else
                res += QChar(text[i]);
            i++;
        }
    }
    res = RaiseUpFirstLetters(res);
    return res;
}

QString A2LConversion::convert(QProgressDialog* prg, bool /*wikiMode*/)
{
    strResult = convert(prg, strSource);
	return strResult;
}

QChar A2LConversion::ConvertSessizChar(QChar c)
{
    if (c == QChar('\x28', '\x06'))
        return 'b';

    else if (c == QChar('\x2a', '\x06') || c == QChar('\x37', '\x06'))
        return 't';

    else if (c == QChar('\x2b', '\x06') || c == QChar('\x33', '\x06') || c == QChar('\x35', '\x06'))
        return 's';

    else if (c == QChar('\x2c', '\x06'))
        return 'c';

    else if (c == QChar('\x2d', '\x06') || c == QChar('\x47', '\x06'))
        return 'h';

    else if (c == QChar('\x2e', '\x06'))
        return 'x';

    else if (c == QChar('\x2f', '\x06'))
        return 'd';

    else if (c == QChar('\x30', '\x06') || c == QChar('\x32', '\x06') || c == QChar('\x36', '\x06') || c == QChar('\x38', '\x06'))
        return 'z';

    else if (c == QChar('\x31', '\x06'))
        return 'r';

    else if (c == QChar('\x34', '\x06'))
        return QChar('\x5f', '\x01');

    else if (c == QChar('\x39', '\x06'))
        return '\'';

    else if (c == QChar('\x3a', '\x06'))
        return QChar('\x1f', '\x01');

    else if (c == QChar('\x41', '\x06'))
        return 'f';

    else if (c == QChar('\x42', '\x06'))
        return 'q';

    else if (c == QChar('\x44', '\x06'))
        return 'l';

    else if (c == QChar('\x45', '\x06'))
        return 'm';

    else if (c == QChar('\x46', '\x06'))
        return 'n';

    else if (c == QChar('\x48', '\x06'))
        return 'v';

    else if (c == QChar('\x7e', '\x06'))
        return 'p';

    else if (c == QChar('\x86', '\x06'))
        return QChar('\xe7', '\x00');

    else if (c == QChar('\x98', '\x06'))
        return 'j';

    else if (c == QChar('\xa9', '\x06'))
        return 'k';

    else if (c == QChar('\xaf', '\x06'))
        return 'g';

    else if (c == QChar('\xcc', '\x06'))
        return 'y';


    return 'a';
}


QString A2LConversion::ConvertWord(const QString& wo, int bf, bool /*beforeVs*/)
{
    QString word(wo);

    if (word.isNull() || word.isEmpty())
        return "";

    /*if (word[word.length() - 1] == QChar('\x59', '\x02'))
        word = word.mid(0, word.length() - 1);*/

    if (IsNonConvertableWord(word))
        return word;

    QString w = "";

    //int ind = word.lastIndexOf("\u200c");
    //if (ind > -1)

    if (word.contains("\u200c"))
    {
        int length = 0;
        int num3 = word.length();
        for (int i = num3 - 1; i > 0; i--)
        {
            if (word[i] == QChar('\x59', '\x02'))
            {
                length = i;
                break;
            }
        }
        if (length != 0)
        {
            int num4 = ChooseBackOrFront(word.mid(0, length));
            if (3 == num4)
                num4 = 2;

            QString str2 = ConvertWord(word.mid(length + 1, num3 - (length + 1)), num4, false);
            int num5 = ChooseBackOrFront(str2);
            QString str3 = ConvertWord(word.mid(0, length), num5, false);
            int num6 = ChooseBackOrFront(str3);
            if (num6 != num5)
                str2 = ConvertWord(word.mid(length + 1, num3 - (length + 1)), num6, false);

            return (str3 + str2);
        }
    }
    w = GetWordFromDictionary(word);
    if (w == "")
    {
        if (word.contains("\u200c"))
        {
            //If the first part is in dictionary then replace it:
            int ind = word.indexOf("\u200c");
            QString fpart = word.mid(0, ind);
            QString eq;
            if (!(eq = GetWordFromDictionary(fpart)).isEmpty())
                word = eq + word.mid(word.indexOf("\u200c") + 1);
        }

        word = ChangePostfixes(word);
        if (word == "")
            return "";

        int num7 = ChooseBackOrFront(word);
        if (3 == num7)
            num7 = 2;

        /*if (1 == num7)*/
            word = word.replace("\u06cc\u06cc\u06cc", "iyi");

        if (2 == num7)
            word = word.replace("\u06cc\u06cc", "y\u0131");

        //Ereb xettinde "en" tenvini:
        word = word.replace("\u0627\u064b", "\u0259n");

        //Arabic "eh" and then virtual space and then "y" or "v":
        word = word.replace("\u0647\u200c\u06cc", "\u0259y");
        word = word.replace("\u0647\u200c\u0648", "\u0259v");

        //Arabic "eh" and then virtual space:
        word = word.replace("\u0647\u200c", "\u0259");
        word = DescriptWord(word);
        w = "";
        int num8 = word.length();
        for (int j = 0; j < num8; j++)
        {
            QChar c = word[j];
            if (j == 0)
            {
                if ((c == QChar('\x27', '\x06')) && (word.length() == 1))
                {
                    w = w + "a";
                    j++;
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && (word[1] == QChar('\xcc', '\x06')))
                {
                    w = w + "i";
                    j++;
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && (word[1] == QChar('\x26', '\x06')))
                {
                    w = w + "e";
                    j++;
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && (word[1] == QChar('\xce', '\x06')))
                {
                    w = w + "\u0131";
                    j++;
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && (word[1] == QChar('\x24', '\x06')))
                {
                    w = w + "\u00f6";
                    j++;
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && (word[1] == QChar('\x48', '\x06')))
                {
                    w = w + "u";
                    j++;
                    continue;
                }
                if (c == QChar('\x48', '\x06'))
                {
                    w = w + "v";
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && (word[1] == QChar('\xc6', '\x06')))
                {
                    w = w + "\u00fc";
                    j++;
                    continue;
                }
                if ((c == QChar('\x27', '\x06')) && IsSessiz(word[1]))
                {
                    w = w + "\u0259";
                    continue;
                }
                if (c == QChar('\xcc', '\x06'))
                {
                    w = w + "y";
                    continue;
                }
                if (c == QChar('\x39', '\x06'))
                    continue;
            }
            if (IsEnd(word, j) && (c == QChar('\x47', '\x06')))
            {
                w = w + "\u0259";
                j++;
            }
            /*else if (j < num8-1 && c == QChar('\x47', '\x06') && word[j+1] == QChar('\x0c', '\x20'))
            {
                w = w + "\u0259";
                j++;
            }*/
            else if ((c == QChar('\x22', '\x06')) || (c == QChar('\x27', '\x06')))
            {
                w = w + "a";
                continue;
            }
            else if (c == QChar('\x26', '\x06'))
            {
                w = w + "e";
                continue;
            }

            //Tashdid:
            else if (c == QChar('\x51', '\x06'))
            {
                w += w[w.length() - 1];
                continue;
            }

            else if (c == QChar('\x24', '\x06'))
            {
                w = w + "\u00f6";
                continue;
            }

            else if (c == QChar('\x4e', '\x06'))
            {
                w = w + "\u0259";
                continue;
            }
            else if (c == QChar('\x48', '\x06') && IsSessizYV(word, j))
            //else if (c == QChar('\x48', '\x06') && IsSesli(word[j - 1]))
            {
                w = w + "v";
                continue;
            }
            else if (c == QChar('\xcc', '\x06') && IsSessizYV(word, j))
            {
                w += "y";
                continue;
            }
            else
            {
                if (c == QChar('\xc6', '\x06'))
                {
                    w = w + "\u00fc";
                    continue;
                }

                else if (c == QChar('\xce', '\x06'))
                {
                    w = w + "\u0131";
                    continue;
                }

                else if (c == QChar('\x48', '\x06'))
                {
                    //Handling the emailed note about 'o', 'u' and etc:
                    if (word[j-1] == QChar('\x42', '\x06') || word[j-1] == QChar('\x3a', '\x06'))
                    {
                        int hica = GetHicaNumber(word, j);
                        /*if (hica == 1)      //This is sometimes incorrect!
                        {
                            continue;
                        }
                            w += "o";
                        else*/ if (hica == 2)
                        {
                            w += "u";
                            continue;
                        }
                    }

                    if ((bf == 0) || (3 == bf))
                        bf = ChooseBackOrFront(word);
                    if (3 == bf)
                        bf = ChooseBackOrFront(w);
                    if (3 == bf)
                        bf = 2;
                    int num10 = ChooseBackOrFront(word);
                    if ((2 == num10) || (1 == num10))
                        bf = num10;
                    if (2 == bf)
                        w = w + "u";
                    else if (1 == bf)
                        w = w + "\u00fc";
                    continue;
                }
                if (c == QChar('\xcc', '\x06') && ((IsSesli(word[j - 1]) && word[j - 1] != QChar('\x48', '\x06')) || (j != (word.length() - 1) && IsSesli(word[j + 1]) && word[j+1] != QChar('\x48', '\x06') && word[j+1] != QChar('\xcc', '\x06'))))
                    w = w + "y";
                else
                {
                    if (c == QChar('\x0c', '\x20') || c == '?' || c == QChar('\x39', '\x06'))
                        continue;

                    else if (c == QChar('\x23', '\x06'))
                    {
                        w = w + "\u0259";
                        continue;
                    }

                    else if (c == QChar('\xcc', '\x06'))
                    {
                        if ((bf == 0) || (3 == bf))
                            bf = ChooseBackOrFront(word);
                        if (3 == bf)
                            bf = ChooseBackOrFront(w);
                        if (3 == bf)
                            bf = 2;
                        int num11 = ChooseBackOrFront(word);
                        if ((2 == num11) || (1 == num11))
                            bf = num11;
                        if (2 == bf)
                            w = w + "\u0131";
                        else if (1 == bf)
                            w = w + "i";
                        continue;
                    }

                    if (IsSessiz(c))
                        w = w + QString(ConvertSessizChar(c));
                    else if (c == QChar('\x47', '\x06'))
                        w = w + "h";
                    else
                        w = w + QString(c);
                }
            }
        }
    }
    return w;
}


int A2LConversion::GetHicaNumber(const QString& word, int index)
{
    int hica = 0;
    for(int i=0; i<word.length() && i <= index; i++)
    {
        if (IsSesli(word[i]) || ((word[i] == QChar('\x48', '\x06') || word[i] == QChar('\xcc', '\x06')) &&!IsSessizYV(word, i)))
            hica++;
    }

    return hica;
}


QString A2LConversion::DescriptWord(const QString& w)
{
    if (w.isNull() || w.isEmpty())
        return "";

    QString str(w);
    if (IsSessiz(str, 0) && IsSessiz(str, 1))
        str = str.insert(1, "\u0259");

    if (!ContainsBackVowel(w))
    {
        int length = str.length();
        for (int i = 0; i < (length - 1); i++)
        {
            if (((IsSessiz(str, i) && (str[i] != QChar('\x46', '\x06'))) && ((str[i] != QChar('\x33', '\x06')) && (str[i] != QChar('\x44', '\x06')))) && ((str[i] != QChar('\x31', '\x06')) && IsSessiz(str, i + 1)))
            {
                str = str.insert(i + 1, "\u0259");
                length++;
            }
            else
            {
                IsSessiz(str, i + 1);       //What does this line do?!
                IsSessiz(str, i - 1);       //"
                if ((((str[i] == QChar('\x46', '\x06')) || (str[i] == QChar('\x33', '\x06'))) || ((str[i] == QChar('\x44', '\x06')) || (str[i] == QChar('\x31', '\x06')))) && (IsSessiz(str, i + 1) && IsSessiz(str, i - 1)))
                {
                    str = str.insert(i + 1, "\u0259");
                    length++;
                }
            }
        }
        int num3 = 0;
        for (int j = 0; j < length; j++)
        {
            if (IsSesli(str, j) || (str[j] == QChar('\x59', '\x02')))
                num3 = 0;
            else if (IsSessiz(str, j))
                num3++;
            if (((num3 == 2) && (j < (length - 2))) && (IsSessiz(str, j + 1) && IsSesli(str, j + 2)))
            {
                str = str.insert(j + 1, "\u0259");
                length++;
                num3 = 0;
            }
            else if (((num3 == 3) && (j < (length - 1))) && IsSessiz(str, j + 1))
            {
                str = str.insert(j, "\u0259");
                length++;
                num3 = 0;
            }
        }
    }
    return str;
}

QString A2LConversion::GetResult()
{
    return strResult;
}

QChar A2LConversion::GetSecondSesli(const QString& w)
{
    int num = 0;
    for (int i = 0; i < w.length(); i++)
    {
        if (IsLatinSesli(w[i]))
            num++;
        if (num == 2)
            return w[i];
    }
    return ' ';
}

QChar A2LConversion::GetSpecialChar(QChar c)
{
    if (c == QChar('\x0c', '\x06'))
        return ',';

    else if (c == QChar('\x1b', '\x06'))
        return ';';

    else if (c == QChar('\x1f', '\x06'))
        return '?';

    return ' ';
}

QString A2LConversion::GetWord(int i)
{
    QString str = "";
    QChar c = strSource[i];
    int length = strSource.length();
    while (IsCharAInWordChar(c))
    {
        str = str + QString(c);
        i++;
        if (i >= length)
            return str;

        c = strSource[i];
    }
    return str;
}

QString A2LConversion::GetWordFromDictionary(const QString& wo)
{
    QString word(wo);
    //Remove tashdid:
    word = word.replace("\u0651", "");
    word = "[" + word + "]";
    if (!AA2AL.contains(word))
        return "";

    int index = AA2AL.indexOf(word);
    while (AA2AL[index] != '=')
        index++;
    index++;
    int num2 = index;
    QString str = "";
    while (((num2 < AA2AL.length()) && (AA2AL[num2] != '\r')) && (AA2AL[num2] != '\n'))
    {
        str = str + QString(AA2AL[num2]);
        num2++;
    }
    return str;
}

bool A2LConversion::IsCharAEndStatementChar(QChar c) const
{
    return (c == '?' || c == QChar('\x1f', '\x06') || c == '.' || c == '!');
}

bool A2LConversion::IsCharAInWordChar(QChar c) const
{
    return (c != ' ' && c != '\n' && c != '\t' && c != '\r' && c != '?' && c != '.' && c != '!' && c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}' && c != '"' && c != '-' && c != '=' && c != ',' && c != QChar('\x0c', '\x06') && c != QChar('\x1c', '\x20') && c != QChar('\x1d', '\x20') && c != ':' && c != ';' && c != QChar('\x1b', '\x06') && c != QChar('\xbb', '\x00') && c != QChar('\xab', '\x00') && c != QChar('\x1f', '\x06'));
}

bool A2LConversion::IsEnd(const QString& w, int ind)
{
    return (ind == (w.length() - 1));// || w[ind + 1] == QChar('\x59', '\x02'));
}

QString A2LConversion::IslahEt(const QString& word)
{
    QString w(word);

    if (!w.isNull() && !w.isEmpty() && w.length() >= 3 && w[0] == QChar('\x31', '\x01') && GetSecondSesli(w) == 'a')
        w = "i" + w.mid(1, w.length() - 1);
    return w;
}

bool A2LConversion::IsLatinSesli(QChar c)
{
    return (c == QChar('\x59', '\x02') || c == 'a' || c == QChar('\x31', '\x01') || c == 'u' ||
            c == 'o' || c == 'e' || c == QChar('\xf6', '\x00') || c == QChar('\xfc', '\x00'));
}

bool A2LConversion::IsNonConvertableWord(const QString& /*w*/)
{
    return false;
}

/*bool A2LConversion::IsAbsSesli(QChar c)
{
    return (
            c == QChar()
            );
}*/

bool A2LConversion::IsSesli(QChar c)
{
    return (c == QChar('\x27', '\x06') || c == QChar('\x22', '\x06') || c == QChar('\xcc', '\x06') || c == QChar('\x48', '\x06') || c == QChar('\x24', '\x06') ||
            c == QChar('\x26', '\x06') || c == QChar('\xc6', '\x06') || c == QChar('\xce', '\x06') || c == QChar('\x4e', '\x06'));
}

bool A2LConversion::IsSesli(const QString& w, int ind)
{
    if ((w[ind] != QChar('\x47', '\x06')) || !IsEnd(w, ind))
    {
        if (IsSesli(w[ind]))
            return true;
        if (w[ind] != 'a' && w[ind] != 'i' && w[ind] != QChar('\x59', '\x02'))
            return false;
    }
    return true;
}

bool A2LConversion::IsSessiz(QChar c)
{
    return (c == QChar('\x28', '\x06') || c == QChar('\x7e', '\x06') || c == QChar('\x2a', '\x06') || c == QChar('\x2b', '\x06') ||
            c == QChar('\x2c', '\x06') || c == QChar('\x86', '\x06') || c == QChar('\x2d', '\x06') || c == QChar('\x2e', '\x06') ||
            c == QChar('\x2f', '\x06') || c == QChar('\x30', '\x06') || c == QChar('\x31', '\x06') || c == QChar('\x32', '\x06') ||
            c == QChar('\x98', '\x06') || c == QChar('\x33', '\x06') || c == QChar('\x34', '\x06') || c == QChar('\x35', '\x06') ||
            c == QChar('\x36', '\x06') || c == QChar('\x37', '\x06') || c == QChar('\x38', '\x06') || c == QChar('\x39', '\x06') ||
            c == QChar('\x3a', '\x06') || c == QChar('\x41', '\x06') || c == QChar('\x42', '\x06') || c == QChar('\xa9', '\x06') ||
            c == QChar('\xaf', '\x06') || c == QChar('\x44', '\x06') || c == QChar(QChar('\x45', '\x06')) || c == QChar('\x46', '\x06'));
}

bool A2LConversion::IsSessiz(const QString& w, int ind)
{
    if ((ind >= w.length()) || (ind < 0))
        return false;
    if (IsSessiz(w[ind]))
        return true;
    if (w[ind] == QChar(QChar('\x47', '\x06')))
    {
        if (IsEnd(w, ind))
            return false;
        return true;
    }
    if (IsLatinSesli(w[ind]))
        return false;
    return IsSessizYV(w, ind);
}

bool A2LConversion::IsSessizYV(const QString& w, int ind)
{
    //If it's not Y or V then return false:
    if ((w[ind] != QChar('\x48', '\x06')) && (w[ind] != QChar('\xcc', '\x06')))
        return false;

    if (ind == 0)
        return true;
    if (ind == 1)
    {
        if (w[0] == QChar('\x22', '\x06'))
            return true;
        return false;
    }
    /*if (IsSesli(w[ind-1]) || IsLatinSesli(w[ind-1]))
        return true;*/
    if (IsSessiz(w[ind-1]))
        return false;
    if (w[ind-1] == QChar('\x48', '\x06') || w[ind-1] == QChar('\xcc', '\x06'))
        return !IsSessizYV(w, ind-1);
    if (IsSesli((w[ind-1])) || IsLatinSesli(w[ind-1]))
        return true;
    if ((!IsSesli(w[ind - 1]) || w[ind - 1] == QChar('\xcc', '\x06')) && (ind >= w.length() - 1 || !IsSesli(w[ind + 1])))
        return false;

    return true;
}

/*void A2LConversion::openDicts()
{
	QString path = QCoreApplication::applicationDirPath();
    path = path + QDir::separator() + "dicts" + QDir::separator();
    QFile file(path + "dict_AzA2AzL.dat");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        AA2AL = QString::fromUtf8(file.readAll());
    }
    else
    {
        QMessageBox::warning(NULL, tr("Dictionary"), tr("File not found!\nWorking in non dictionary mode!", "Error"));
        AA2AL = "";
        return;
    }

    QFile file2(path + "dict_AzA2AzL_user.dat");
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        AA2AL += QString::fromUtf8(file2.readAll());
    }
    else
        return;
}*/

QString A2LConversion::RaiseUpFirstLetters(const QString& text) const
{
	QString res;
    int length = text.length();
    bool flag = true;
    for (int i = 0; i < length; i++)
    {
        if (IsCharAInWordChar(text[i]) && flag)
        {
            QString str = text.mid(0, i) + ((text[i] == 'i') ? "\u0130" : QString(QChar(text[i]).toUpper())) + text.mid(i + 1);
            flag = false;
            res = str;
        }
        else if (IsCharAEndStatementChar(text[i]))
            flag = true;
    }
	
	return res;
}
