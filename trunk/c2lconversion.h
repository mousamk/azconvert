#ifndef C2LCONVERSION_H
#define C2LCONVERSION_H

#include <QObject>
#include <QString>
#include <QProgressDialog>
#include "convertor.h"


class C2LConversion : public Convertor
{
public:
    C2LConversion(QObject* parent);
    QString convert(QProgressDialog* progressDialog);
    QString convert(QString text);
    void    reloadResources();
    Qt::LayoutDirection getSourceLayoutDirection();
    Qt::LayoutDirection getDestinationLayoutDirection();
    QString getTablesPostfix();
    bool canAddWords();
    
    
protected:
    /*!
     * @brief Fetches the record for a character and returns all parts in a string list.
     * @param query The query to get the fields from.
     * @param record The record to get the fields' indexes from.
     * @returns The list of fields for a character record.
     */
    QStringList getCharacterTuple(const QSqlQuery& query, const QSqlRecord& record);
};

#endif // C2LCONVERSION_H
