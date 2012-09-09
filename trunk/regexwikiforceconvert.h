/*!
 * @file regexwikiforceconvert.h
 * @brief This file contains declaration of RegexWikiForceConvert class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKIFORCECONVERT_H
#define REGEXWIKIFORCECONVERT_H

#include "regex.h"

class Convertor;


/*!
 * @brief The Wiki force convert template checker Regex class.
 */
class RegexWikiForceConvert : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexWikiForceConvert(QString& source);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXWIKIFORCECONVERT_H
