/********************************************************************************
** Form generated from reading ui file 'calendarswitchdialog.ui'
**
** Created: Mon Sep 7 22:14:16 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CALENDARSWITCHDIALOG_H
#define UI_CALENDARSWITCHDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CalendarSwitchDialog
{
public:
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txtGrYear;
    QComboBox *cboGrMonth;
    QLabel *label_3;
    QComboBox *cboGrDay;
    QCheckBox *chkAzMonthes;
    QGroupBox *groupBox_2;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *txtJaYear;
    QComboBox *cboJaMonth;
    QLabel *label_6;
    QComboBox *cboJaDay;
    QPushButton *btnGr2Ja;
    QPushButton *btnJa2Gr;
    QPushButton *btnClose;
    QLabel *label_7;

    void setupUi(QDialog *CalendarSwitchDialog)
    {
        if (CalendarSwitchDialog->objectName().isEmpty())
            CalendarSwitchDialog->setObjectName(QString::fromUtf8("CalendarSwitchDialog"));
        CalendarSwitchDialog->resize(543, 348);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        CalendarSwitchDialog->setFont(font);
        CalendarSwitchDialog->setModal(true);
        groupBox = new QGroupBox(CalendarSwitchDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 221, 261));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 46, 14));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 100, 46, 14));
        txtGrYear = new QLineEdit(groupBox);
        txtGrYear->setObjectName(QString::fromUtf8("txtGrYear"));
        txtGrYear->setGeometry(QRect(50, 50, 121, 20));
        cboGrMonth = new QComboBox(groupBox);
        cboGrMonth->setObjectName(QString::fromUtf8("cboGrMonth"));
        cboGrMonth->setGeometry(QRect(50, 120, 121, 22));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 170, 46, 14));
        cboGrDay = new QComboBox(groupBox);
        cboGrDay->setObjectName(QString::fromUtf8("cboGrDay"));
        cboGrDay->setGeometry(QRect(50, 190, 121, 22));
        chkAzMonthes = new QCheckBox(CalendarSwitchDialog);
        chkAzMonthes->setObjectName(QString::fromUtf8("chkAzMonthes"));
        chkAzMonthes->setGeometry(QRect(20, 280, 141, 20));
        groupBox_2 = new QGroupBox(CalendarSwitchDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(310, 10, 221, 261));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 30, 46, 14));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 100, 46, 14));
        txtJaYear = new QLineEdit(groupBox_2);
        txtJaYear->setObjectName(QString::fromUtf8("txtJaYear"));
        txtJaYear->setGeometry(QRect(50, 50, 121, 20));
        cboJaMonth = new QComboBox(groupBox_2);
        cboJaMonth->setObjectName(QString::fromUtf8("cboJaMonth"));
        cboJaMonth->setGeometry(QRect(50, 120, 121, 22));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 170, 46, 14));
        cboJaDay = new QComboBox(groupBox_2);
        cboJaDay->setObjectName(QString::fromUtf8("cboJaDay"));
        cboJaDay->setGeometry(QRect(50, 190, 121, 22));
        btnGr2Ja = new QPushButton(CalendarSwitchDialog);
        btnGr2Ja->setObjectName(QString::fromUtf8("btnGr2Ja"));
        btnGr2Ja->setGeometry(QRect(240, 90, 61, 23));
        btnJa2Gr = new QPushButton(CalendarSwitchDialog);
        btnJa2Gr->setObjectName(QString::fromUtf8("btnJa2Gr"));
        btnJa2Gr->setGeometry(QRect(240, 160, 61, 23));
        btnClose = new QPushButton(CalendarSwitchDialog);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(457, 316, 75, 23));
        label_7 = new QLabel(CalendarSwitchDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 310, 401, 31));
        label_7->setWordWrap(true);

        retranslateUi(CalendarSwitchDialog);
        QObject::connect(btnClose, SIGNAL(clicked()), CalendarSwitchDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(CalendarSwitchDialog);
    } // setupUi

    void retranslateUi(QDialog *CalendarSwitchDialog)
    {
        CalendarSwitchDialog->setWindowTitle(QApplication::translate("CalendarSwitchDialog", "Calendar convert", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("CalendarSwitchDialog", "Gregorian Calendar", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CalendarSwitchDialog", "Year:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("CalendarSwitchDialog", "Month:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("CalendarSwitchDialog", "Day:", 0, QApplication::UnicodeUTF8));
        chkAzMonthes->setText(QApplication::translate("CalendarSwitchDialog", "Azerbaijani monthes", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("CalendarSwitchDialog", "Iranian Calendar", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("CalendarSwitchDialog", "Year:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("CalendarSwitchDialog", "Month:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("CalendarSwitchDialog", "Day:", 0, QApplication::UnicodeUTF8));
        btnGr2Ja->setText(QApplication::translate("CalendarSwitchDialog", "==>", 0, QApplication::UnicodeUTF8));
        btnJa2Gr->setText(QApplication::translate("CalendarSwitchDialog", "<==", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("CalendarSwitchDialog", "Close", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("CalendarSwitchDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#ff0000;\">Note: The algorithm used here, may have inaccurate result for dates outside the range 1925-2088!</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(CalendarSwitchDialog);
    } // retranslateUi

};

namespace Ui {
    class CalendarSwitchDialog: public Ui_CalendarSwitchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARSWITCHDIALOG_H
