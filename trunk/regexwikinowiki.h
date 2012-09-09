/*!
 * @file regexwikinowiki.h
 * @brief This file contains declaration of RegexWikiNoWiki class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKINOWIKI_H
#define REGEXWIKINOWIKI_H

#include "regex.h"

class Convertor;


/*!
 * @brief The Wiki NoConvert template checker Regex class.
 */
class RegexWikiNoWiki : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor engine which may be used to convert some pieces
     */
    RegexWikiNoWiki(QString& source, Convertor* convertor);

    //! @brief Class destructor
    ~RegexWikiNoWiki();


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

#endif // REGEXWIKINOWIKI_H
