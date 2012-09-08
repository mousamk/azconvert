/*!
 * @file regex.h
 * @brief This file contains declaration of abstract base Regex class.
 * @author Mousa Moradi
 */

#ifndef REGEX_H
#define REGEX_H

#include <QString>
#include <QRegExp>
#include <QMap>


//Forward declarations:
class Convertor;


/*!
 * @brief The abstract base class for RegEx checker classes.
 */
class Regex
{
public:
    /*!
     * @brief Class constructor.
     * @param source The source text to work on it
     */
    Regex(QString& source, Convertor* convertor);

    /*!
     * @brief Class destructor.
     */
    virtual ~Regex();

    /*!
     * @brief This does the main job of search, extract and replace.
     * @returns Returns whether some match is found or not.
     */
    bool run();

    /*!
     * @brief Gets the results and returns them.
     * @returns Returns the results
     */
    const QMap<int, QString>& getResults();

    /*!
     * @brief Resets the holder number
     */
    static void reset();


protected:
    /*!
     * @brief Reads the regexp.cap() and gets the equivalent for the matched substrings
     * @return The equivalent for the matched substrings. It may be the same as first matched one.
     */
    virtual QString getMatchEquivalent() = 0;


private:
    //! @brief This holds the place holder counter
    static int holderNumber;


protected:
    //! @brief The source text to work on it
    QString& source;

    //! @brief The regular expression
    QRegExp regexp;

    //! @brief The extracted (and converted) substrings will be saved in this
    QMap<int, QString> placesHeld;

    //! @brief The convertor engine to be used when necessary
    Convertor* convertor;
};

#endif // REGEX_H
