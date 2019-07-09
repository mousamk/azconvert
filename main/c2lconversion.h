#ifndef C2LCONVERSION_H
#define C2LCONVERSION_H

#include <QObject>
#include <QString>
#include <QtWidgets/QProgressDialog>
#include "convertor.h"


class C2LConversion : public Convertor
{
public:
    C2LConversion(QObject* parent);
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

    /*!
     * @brief Gets a text and replaces some characters in it according to the 'nodiac' table.
     * @param text The text to replace its special characters.
     */
    void replaceSpecialChars(QString& text);
};

#endif // C2LCONVERSION_H
