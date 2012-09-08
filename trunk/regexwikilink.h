/*!
 * @file regexwikilink.h
 * @brief This file contains declaration of RegexWikiLink class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKILINK_H
#define REGEXWIKILINK_H

#include "regex.h"


/*!
 * @brief The Wiki link checker Regex class.
 */
class RegexWikiLink : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexWikiLink(QString& source, Convertor* convertor);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXWIKILINK_H
