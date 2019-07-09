#include <QtWidgets/QMessageBox>
#include <QIntValidator>
#include <QTranslator>

#include "calendarswitchdialog.h"
#include "calendarconverter.h"
#include "settings.h"
#include "util.h"



CalendarSwitchDialog::CalendarSwitchDialog(QWidget *parent) :
    QDialog(parent){
    m_ui.setupUi(this);
    //setFixedSize(543, 348);
    setFixedSize(geometry().width(), geometry().height());

    //Fill days' comboboxes:
    for(int i=1; i<=31; i++)
    {
        m_ui.cboGrDay->addItem(QString::number(i));
        m_ui.cboJaDay->addItem(QString::number(i));
    }

    //Fill monthes' comboboxes:
    FillAzerbaijaniMonthesBox();
    m_ui.cboJaMonth->addItem("\u0641\u0631\u0648\u0631\u062f\u06cc\u0646");
    m_ui.cboJaMonth->addItem("\u0627\u0631\u062f\u06cc\u0628\u0647\u0634\u062a");
    m_ui.cboJaMonth->addItem("\u062e\u0631\u062f\u0627\u062f");
    m_ui.cboJaMonth->addItem("\u062a\u06cc\u0631");
    m_ui.cboJaMonth->addItem("\u0645\u0631\u062f\u0627\u062f");
    m_ui.cboJaMonth->addItem("\u0634\u0647\u0631\u06cc\u0648\u0631");
    m_ui.cboJaMonth->addItem("\u0645\u0647\u0631");
    m_ui.cboJaMonth->addItem("\u0622\u0628\u0627\u0646");
    m_ui.cboJaMonth->addItem("\u0622\u0630\u0631");
    m_ui.cboJaMonth->addItem("\u062f\u06cc");
    m_ui.cboJaMonth->addItem("\u0628\u0647\u0645\u0646");
    m_ui.cboJaMonth->addItem("\u0627\u0633\u0641\u0646\u062f");

    //Set validators for text boxes:
    QValidator* validator = new QIntValidator(NULL);
    m_ui.txtGrYear->setValidator(validator);
    m_ui.txtJaYear->setValidator(validator);

    //Retranslate UI:
    //TRANSLATE_MUI(Settings::GetInstance(this->parent())->getLanguage());
    /*QTranslator translator;
    translator.load(QString("../../trunk/azconvert_az_IR.qm"));
    QApplication::instance()->installTranslator(&translator);
    this->setLayoutDirection(tr("LTR") == "LTR" ? Qt::LeftToRight : Qt::RightToLeft);
    m_ui.retranslateUi(this);*/
}


void CalendarSwitchDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui.retranslateUi(this);
        break;
    default:
        break;
    }
}


void CalendarSwitchDialog::FillAzerbaijaniMonthesBox()
{
    int ind = m_ui.cboGrMonth->currentIndex();
    if (ind == -1)
        ind = 0;

    m_ui.cboGrMonth->clear();
    if (m_ui.chkAzMonthes->isChecked())
    {
        m_ui.cboGrMonth->addItem("Yanavar");
        m_ui.cboGrMonth->addItem("Fevral");
        m_ui.cboGrMonth->addItem("Mart");
        m_ui.cboGrMonth->addItem("Aprel");
        m_ui.cboGrMonth->addItem("May");
        m_ui.cboGrMonth->addItem("\u0130yun");
        m_ui.cboGrMonth->addItem("\u0130yul");
        m_ui.cboGrMonth->addItem("Avqust");
        m_ui.cboGrMonth->addItem("Sentyabr");
        m_ui.cboGrMonth->addItem("Oktyabr");
        m_ui.cboGrMonth->addItem("Noyabr");
        m_ui.cboGrMonth->addItem("Dekabr");
    }
    else
    {
        m_ui.cboGrMonth->addItem("January");
        m_ui.cboGrMonth->addItem("February");
        m_ui.cboGrMonth->addItem("March");
        m_ui.cboGrMonth->addItem("April");
        m_ui.cboGrMonth->addItem("May");
        m_ui.cboGrMonth->addItem("June");
        m_ui.cboGrMonth->addItem("July");
        m_ui.cboGrMonth->addItem("August");
        m_ui.cboGrMonth->addItem("September");
        m_ui.cboGrMonth->addItem("October");
        m_ui.cboGrMonth->addItem("November");
        m_ui.cboGrMonth->addItem("December");
    }

    m_ui.cboGrMonth->setCurrentIndex(ind);
}



void CalendarSwitchDialog::on_chkAzMonthes_stateChanged(int )
{
    FillAzerbaijaniMonthesBox();
}



void CalendarSwitchDialog::on_btnGr2Ja_clicked()
{
    bool ok;
    int gy = m_ui.txtGrYear->text().toInt(&ok, 10);
    int gm = m_ui.cboGrMonth->currentIndex() + 1;
    int gd = m_ui.cboGrDay->currentIndex() + 1;
    int jy, jm, jd;

    if(CalendarConverter::Gregorian2Jalali(jy, jm, jd, gy, gm, gd))
    {
        jm--;
        jd--;
        m_ui.txtJaYear->setText(QString::number(jy));
        m_ui.cboJaMonth->setCurrentIndex(jm);
        m_ui.cboJaDay->setCurrentIndex(jd);
    }
    else
        QMessageBox::warning(NULL, tr("Date"), tr("The date you entered, is not valid!"));
}


void CalendarSwitchDialog::on_btnJa2Gr_clicked()
{
    bool ok;
    int jy = m_ui.txtJaYear->text().toInt(&ok, 10);
    int jm = m_ui.cboJaMonth->currentIndex() + 1;
    int jd = m_ui.cboJaDay->currentIndex() + 1;
    int gy, gm, gd;

    if(CalendarConverter::Jalali2Gregorian(gy, gm, gd, jy, jm, jd))
    {
        gm--;
        gd--;
        m_ui.txtGrYear->setText(QString::number(gy));
        m_ui.cboGrMonth->setCurrentIndex(gm);
        m_ui.cboGrDay->setCurrentIndex(gd);
    }
    else
        QMessageBox::warning(NULL, tr("Date"), tr("The date you entered, is not valid!"));
}









