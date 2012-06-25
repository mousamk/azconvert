#include "convertor.h"
#include "dbservice.h"


Convertor::Convertor(QObject *parent)
    : QObject(parent)
{
}


Convertor::~Convertor()
{
    //Clear array:
    for (int i=0; i<numOfChars; i++)
        delete[] chars[i];
    delete[] chars;
}


/*void Convertor::loadChars()
{
    DbService::getInstance()->loadCharacters(chars, "characters" + getTablesPostfix());
}*/
