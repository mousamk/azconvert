#include <QVariant>
#include "c2lconversion.h"
#include "dbservice.h"


C2LConversion::C2LConversion(QObject* parent)
    : Convertor(parent)
{
    loadChars();
}


Qt::LayoutDirection C2LConversion::getSourceLayoutDirection()
{
    return Qt::LeftToRight;
}


Qt::LayoutDirection C2LConversion::getDestinationLayoutDirection()
{
    return Qt::LeftToRight;
}


/*void C2LConversion::getTablesPostfix()
{
    return "_c2l";
}*/


void C2LConversion::loadChars()
{
    //TODO: Update this code for this mode of conversion!
    QSqlRecord record;
    QSqlQuery query;
    DbService::getInstance()->getCharacters("_l2a", record, query);
    int size = query.size();
    if (size <= 0)      //If size could not be determined
        size = 100;
    numOfChars = size;
    chars = new QString*[numOfChars];
    int i=0;
    while(query.next())
    {
        //TODO: Guard larger than 100 rows!
        chars[i] = new QString[7];
        chars[i][0] = query.value(record.indexOf("source")).toString();
        chars[i][1] = query.value(record.indexOf("start")).toString();
        chars[i][2] = query.value(record.indexOf("mid")).toString();
        chars[i][3] = query.value(record.indexOf("end")).toString();
        chars[i][4] = query.value(record.indexOf("start_voc")).toString();
        chars[i][5] = query.value(record.indexOf("mid_voc")).toString();
        chars[i][6] = query.value(record.indexOf("end_voc")).toString();
        
        i++;
    }
}


QString C2LConversion::convert(QProgressDialog* progressDialog)
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

