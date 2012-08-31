/*!
 * @file util.h
 * @brief This file contain declaration or definition of some utilities to be used
 *  in the files which needs them.
 *
 * @author Mousa Moradi
 */

#ifndef UTIL_H
#define UTIL_H


//Define special characters:
#define CHAR_IH QChar('\x30', '\x01')
#define CHAR_iH QChar('\x31', '\x01')


#define DELETE_AND_NULL(p) if (NULL != p) {delete p; p = NULL;}


#define CHAR_TO_LOWER(c, lc) if (c == 'I') lc = CHAR_iH; else lc = c.toLower()
#define WORD_TO_LOWER(w, lw) lw = w; lw.replace('I', CHAR_iH); lw = lw.toLower()


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
