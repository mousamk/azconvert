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

#define IS_EVEN(p) (p%2==0)

#define CHAR_TO_LOWER(c, lc) if (c == 'I') lc = CHAR_iH; else if (c == CHAR_IH) lc = 'i'; else lc = c.toLower()
#define WORD_TO_LOWER(w, lw) lw = w; lw.replace('I', CHAR_iH); lw.replace(CHAR_IH, 'i'); lw = lw.toLower()


#define TRANSLATE(LANG) QTranslator translator; \
    translator.load(QString("../../trunk/azconvert_") + LANG + QString(".qm")); \
    QApplication::instance()->installTranslator(&translator); \
    this->setLayoutDirection(tr("LTR") == "LTR" ? Qt::LeftToRight : Qt::RightToLeft); \
    ui->retranslateUi(this)


#define TRANSLATE_MUI(LANG) QTranslator translator; \
    translator.load(QString("../../trunk/azconvert_") + LANG + QString(".qm")); \
    QApplication::instance()->installTranslator(&translator); \
    this->setLayoutDirection(tr("LTR") == "LTR" ? Qt::LeftToRight : Qt::RightToLeft); \
    m_ui.retranslateUi(this)



class Util
{
public:
};

#endif // UTIL_H
