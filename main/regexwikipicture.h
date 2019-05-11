/*!
 * @file regexwikipicture.h
 * @brief This file contains declaration of RegexWikiPicture class.
 * @author Mousa Moradi
 */

#ifndef REGEXWIKIPICTURE_H
#define REGEXWIKIPICTURE_H

#include "regex.h"

class Convertor;


/*!
 * @brief The Wiki picture checker Regex class.
 */
class RegexWikiPicture : public Regex
{
public:
    /*!
     * @brief Class constructor
     * @param source The source text to work on it
     * @param convertor The convertor engine which may be used to convert some pieces
     */
    RegexWikiPicture(QString& source, Convertor* convertor);

    //! @brief Class destructor
    ~RegexWikiPicture();


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

#endif // REGEXWIKIPICTURE_H
