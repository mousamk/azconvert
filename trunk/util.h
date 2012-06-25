/*!
 * @file util.h
 * @brief This file contain declaration or definition of some utilities to be used
 *  in the files which needs them.
 *
 * @author Mousa Moradi
 */

#ifndef UTIL_H
#define UTIL_H

#define DELETE_AND_NULL(p) if (NULL != p) {delete p; p = NULL;}


/*!
 * @enum ConvertMode
 * @brief This mode specifies transliteration direction.
 */
enum ConvertMode
{
    LatinToArabic = 0,             ///< @brief Latin to Arabic mode
    ArabicToLatin,                 ///< @brief Arabic to Latin mode
    CyrillicToLatin                ///< @brief Cyrillic to latin mode
};


class Util
{
public:

};

#endif // UTIL_H
