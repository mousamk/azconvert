/*!
 * @file regexurl.h
 * @brief This file contains declaration of RegexUrl class.
 * @author Mousa Moradi
 */

#ifndef REGEXURL_H
#define REGEXURL_H

#include "regex.h"


/*!
 * @brief The Url checker Regex class.
 */
class RegexUrl : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexUrl(QString& source, Convertor* convertor);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXURL_H
