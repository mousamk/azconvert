/*!
 * @file specialcharacterrecord.h
 * @brief This files contains declaration of SpecialCharacterRecord struct.
 * @author Mousa Moradi
 */

#ifndef SPECIALCHARACTERRECORD_H
#define SPECIALCHARACTERRECORD_H

#include <QString>


/*!
 * @brief Enumerates different situation when a special character can show up.
 */
enum SpecialCharacterSituation
{
    Neutral = 0x0,      //!< Not important; Everywhere, like ','
    Opening,            //!< In opening of a phrase, like '('
    Closing             //!< In cloding a phrase, like ')'
};


/*!
 * @brief The SpecialCharacterRecord struct contains elements related to a special
 *        character. It matches a record in db, except for ID.
 */
struct SpecialCharacterRecord
{
public:
    SpecialCharacterRecord(QString source, QString equivalent, SpecialCharacterSituation position)
        : source(source), equivalent(equivalent), position(position) {}

public:
    //! @brief Source character
    QString source;

    //! @brief Equivalent character to the source
    QString equivalent;

    //! @brief Situation of the character
    SpecialCharacterSituation position;
};

#endif // SPECIALCHARACTERRECORD_H
