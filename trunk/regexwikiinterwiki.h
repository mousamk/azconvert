/*!
 * @file regexwikiinterwiki.h
 * @brief This file contains declaration of RegexWikiInterwiki class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKIINTERWIKI_H
#define REGEXWIKIINTERWIKI_H

#include "regex.h"


/*!
 * @brief The Wiki interwiki checker Regex class.
 */
class RegexWikiInterwiki : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexWikiInterwiki(QString& source, Convertor* convertor);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXWIKIINTERWIKI_H
