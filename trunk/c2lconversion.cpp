#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include "c2lconversion.h"


C2LConversion::C2LConversion(QObject* parent)
    : Convertor(parent)
{
    reloadResources();
}


void C2LConversion::reloadResources()
{
    loadChars();
    //loadWords();      //Not needed in this direction.
    //loadSolidWords();
    //loadPrefixes();
    //loadPostfixes();
    //loadSpecialChars();
}


Qt::LayoutDirection C2LConversion::getSourceLayoutDirection()
{
    return Qt::LeftToRight;
}


Qt::LayoutDirection C2LConversion::getDestinationLayoutDirection()
{
    return Qt::LeftToRight;
}


QString C2LConversion::getTablesPostfix()
{
    return "_c2l";
}


bool C2LConversion::canAddWords()
{
    return false;
}


QStringList C2LConversion::getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record)
{
    QStringList tuple;
    tuple << query.value(record.indexOf("equivalent")).toString();

    return tuple;
}


QString C2LConversion::convert(QProgressDialog* /*progressDialog*/)
{
    //TODO: Update this method.
    QString str = strSource;
    str.replace("А", "A");
    str.replace("а", "a");
    str.replace("Б", "B");
    str.replace("б", "b");
    str.replace("Ҹ", "C");
    str.replace("ҹ", "c");
    str.replace("Ч", "Ç");
    str.replace("ч", "ç");
    str.replace("Д", "D");
    str.replace("д", "d");
    str.replace("Е", "E");
    str.replace("е", "e");
    str.replace("Ә", "Ə");
    str.replace("ә", "ə");
    str.replace("Ф", "F");
    str.replace("ф", "f");
    str.replace("Ҝ", "G");
    str.replace("ҝ", "g");
    str.replace("Ғ", "Ğ");
    str.replace("ғ", "ğ");
    str.replace("Һ", "H");
    str.replace("һ", "h");
    str.replace("Х", "X");
    str.replace("х", "x");
    str.replace("И", "İ");
    str.replace("и", "i");
    str.replace("Ы", "I");
    str.replace("ы", "ı");
    str.replace("Ж", "J");
    str.replace("ж", "j");
    str.replace("К", "K");
    str.replace("к", "k");
    str.replace("Г", "Q");
    str.replace("г", "q");
    str.replace("Л", "L");
    str.replace("л", "l");
    str.replace("М", "M");
    str.replace("м", "m");
    str.replace("Н", "N");
    str.replace("н", "n");
    str.replace("О", "O");
    str.replace("о", "o");
    str.replace("Ө", "Ö");
    str.replace("ө", "ö");
    str.replace("П", "P");
    str.replace("п", "p");
    str.replace("Р", "R");
    str.replace("р", "r");
    str.replace("С", "S");
    str.replace("с", "s");
    str.replace("Ш", "Ş");
    str.replace("ш", "ş");
    str.replace("Т", "T");
    str.replace("т", "t");
    str.replace("У", "U");
    str.replace("у", "u");
    str.replace("Ү", "Ü");
    str.replace("ү", "ü");
    str.replace("В", "V");
    str.replace("в", "v");
    str.replace("Ј", "Y");
    str.replace("ј", "y");
    str.replace("З", "Z");
    str.replace("з", "z");
    return str;
}

