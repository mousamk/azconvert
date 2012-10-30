#include <QTranslator>

#include "aboutdialog.h"
#include "settings.h"
#include "util.h"


AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    m_ui.setupUi(this);

    //Retranslate UI:
    TRANSLATE_MUI(Settings::GetInstance(parent)->getLanguage());
}
