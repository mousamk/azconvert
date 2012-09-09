#include <QDebug>
#include "regex.h"


//Initialize static member variable:
int Regex::holderNumber = 1;

Regex::Regex(QString &source)
    : source(source)
{
}


Regex::~Regex()
{
}


bool Regex::run()
{
    int index = 0;
    QString match;
    QString holder;
    bool change = false;
    QString equivalent;

    while((index = regexp.indexIn(source, index)) != -1)
    {
        match = regexp.cap();
        equivalent = getMatchEquivalent();

        //qDebug() << "found a match: " << match << "with equivalent" << equivalent << " at position: " << index;

        //Replace the url with a numbered place holder:
        placesHeld.insert(holderNumber, equivalent);
        holder = "{" + QString::number(holderNumber) + "}";
        source.replace(index, match.length(), holder);
        holderNumber++;
        index += holder.length();
        change = true;
    }

    return change;
}


const QMap<int, QString>& Regex::getResults()
{
    return placesHeld;
}


void Regex::reset()
{
    holderNumber = 1;
}
