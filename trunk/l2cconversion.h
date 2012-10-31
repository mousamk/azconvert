#ifndef L2CCONVERSION_H
#define L2CCONVERSION_H

#include <QObject>
#include <QProgressDialog>
#include "convertor.h"


class L2CConversion : public Convertor
{
public:
    L2CConversion(QObject* parent);
    QString convert(QProgressDialog* progressDialog, bool wikiMode);
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

#endif // L2CCONVERSION_H
