/*!
 * @file regexwikitemplate.h
 * @brief This file contains declaration of RegexWikiTemplate class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKITEMPLATE_H
#define REGEXWIKITEMPLATE_H

#include "regex.h"


/*!
 * @brief The Wiki template checker Regex class.
 */
class RegexWikiTemplate : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexWikiTemplate(QString& source);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXWIKITEMPLATE_H
