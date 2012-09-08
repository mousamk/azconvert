/*!
 * @file regexwikipicture.h
 * @brief This file contains declaration of RegexWikiPicture class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKIPICTURE_H
#define REGEXWIKIPICTURE_H

#include "regex.h"


/*!
 * @brief The Wiki picture checker Regex class.
 */
class RegexWikiPicture : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexWikiPicture(QString& source, Convertor* convertor);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXWIKIPICTURE_H
