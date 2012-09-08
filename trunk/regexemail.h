/*!
 * @file regexemail.h
 * @brief This file contains declaration of RegexEmail class.
 * @author Mousa Moradi
 */

#ifndef REGEXEMAIL_H
#define REGEXEMAIL_H

#include "regex.h"


/*!
 * @brief The Email checker Regex class.
 */
class RegexEmail : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     */
    RegexEmail(QString& source, Convertor* convertor);

protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();
};

#endif // REGEXEMAIL_H
