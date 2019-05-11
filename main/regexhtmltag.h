/*!
 * @file regexhtmltag.h
 * @brief This file contains declaration of RegexHtmlTag class.
 * @author Mousa Moradi
 */

#ifndef REGEXHTMLTAG_H
#define REGEXHTMLTAG_H

#include "regex.h"


/*!
 * @brief The Html tag checker Regex class.
 */
class RegexHtmlTag : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexHtmlTag(QString& source);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXHTMLTAG_H
