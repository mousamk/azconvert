#ifndef CHARREPLACERECORD_H
#define CHARREPLACERECORD_H

#include <QString>


/*!
 * @brief The CharReplaceRecord struct contains elements related to a character
 *        replace rule. It matches a record in db.
 */
struct CharReplaceRecord
{
public:
    CharReplaceRecord(int id, QString source, QString equivalent, bool enabled)
        : id(id), source(source), equivalent(equivalent), enabled(enabled) {}

    CharReplaceRecord(const CharReplaceRecord& other)
        : id(other.id), source(other.source), equivalent(other.equivalent), enabled(other.enabled) {}

    CharReplaceRecord() {}


public:
    //! @brief The DB id of this record
    int id;

    //! @brief The source character(s) to be replaced
    QString source;

    //! @brief The equivalent character(s) to replace source
    QString equivalent;

    //! @brief Whether this replacing is enabled or not
    bool    enabled;
};


#endif // CHARREPLACERECORD_H
