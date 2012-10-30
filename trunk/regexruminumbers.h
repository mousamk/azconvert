/*!
 * @file regexwikiruminumbers.h
 * @brief This file contains declaration of RegexRumiNumbers class.
 * @author Mousa Moradi
 */

#ifndef REGEXRUMINUMBERS_H
#define REGEXRUMINUMBERS_H

#include "regex.h"
#include <QMap>


/*!
 * @brief The Rumi numbers convertor regex class.
 */
class RegexRumiNumbers : public Regex
{
public:
    /*!
     * @brief Class construtor
     * @param source The source text to work on it
     */
    RegexRumiNumbers(QString& source);


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    QString getMatchEquivalent();


private:
    //! @brief Contains mapping of rumi numbers to arabic numbers.
    static QMap<QString, QString> rumiNumbers;
};

#endif // REGEXRUMINUMBERS_H
