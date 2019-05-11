/*!
 * @file regexwikinoconvert.h
 * @brief This file contains declaration of RegexWikiNoConvert class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKINOCONVERT_H
#define REGEXWIKINOCONVERT_H

#include "regex.h"


/*!
 * @brief The Wiki NoConvert template checker Regex class.
 */
class RegexWikiNoConvert : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor engine which may be used to convert some pieces
     */
    RegexWikiNoConvert(QString& source);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXWIKINOCONVERT_H
