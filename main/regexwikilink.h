/*!
 * @file regexwikilink.h
 * @brief This file contains declaration of RegexWikiLink class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKILINK_H
#define REGEXWIKILINK_H

#include "regex.h"

class Convertor;


/*!
 * @brief The Wiki link checker Regex class.
 */
class RegexWikiLink : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor to be used in partial converting of links
     */
    RegexWikiLink(QString& source, Convertor* convertor);

    //! @brief Class destructor
    ~RegexWikiLink();


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();


private:
    //! @brief Convertor used to convert pieces
    Convertor* convertor;
};

#endif // REGEXWIKILINK_H
