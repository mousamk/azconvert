/********************************************************************************
** Form generated from reading ui file 'aboutdialog.ui'
**
** Created: Wed Sep 16 22:31:32 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ABOUTDIALOG_H
#define UI_ABOUTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_AboutDialog
{
public:
    QPushButton *btnOk;
    QLabel *label;
    QLabel *label_2;
    QTextBrowser *textBrowser;

    void setupUi(QDialog *AboutDialog)
    {
        if (AboutDialog->objectName().isEmpty())
            AboutDialog->setObjectName(QString::fromUtf8("AboutDialog"));
        AboutDialog->resize(353, 311);
        AboutDialog->setModal(true);
        btnOk = new QPushButton(AboutDialog);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(270, 280, 75, 23));
        label = new QLabel(AboutDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(59, 10, 221, 51));
        QFont font;
        font.setPointSize(28);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(AboutDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(209, 60, 101, 16));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        textBrowser = new QTextBrowser(AboutDialog);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 90, 331, 181));
        textBrowser->setUndoRedoEnabled(true);

        retranslateUi(AboutDialog);
        QObject::connect(btnOk, SIGNAL(clicked()), AboutDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutDialog);
    } // setupUi

    void retranslateUi(QDialog *AboutDialog)
    {
        AboutDialog->setWindowTitle(QApplication::translate("AboutDialog", "About AzConvert", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("AboutDialog", "&OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AboutDialog", "AzConvert", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AboutDialog", "v 3.1", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("AboutDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Created by:</span></p>\n"
"<ul style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Mousa Moradi</li></ul>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Translations:</span></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">Turkish, Azerbaijani, Persian:</span></p>\n"
"<ul style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Not done yet!</li></ul>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p align=\"justify\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">\302\251 Copyright:</span>"
                        "</p>\n"
"<ul style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">This program is free and you can freely copy and/or redistribute it.</li></ul>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Note:</span></p>\n"
"<ol style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Please always check the dedicated weblog for being notified of new releasese</li>\n"
"<li style=\" font-size:10pt;\" align=\""
                        "justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Every help, suggestion, ideo, or ... is appreciated. You cantact us by email or website.</li></ol>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Contact us:</span></p>\n"
"<ul style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">email: 	<a href=\"mailto:mousamk@gmail.com\"><span style=\" text-decoration: underline; color:#0000ff;\">mousamk@gmail.com</span></a></li>\n"
"<li style=\" font-size:10pt;\" align=\""
                        "justify\" style=\" margin-top:0px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">weblog: 	<a href=\"http://azconvert.azeriblog.com\"><span style=\" text-decoration: underline; color:#0000ff;\">http://azconvert.azeriblog.com</span></a></li></ul>\n"
"<p align=\"justify\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:10pt;\"></p>\n"
"<p align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt; font-weight:600;\">Especial thanks to:</span></p>\n"
"<ul style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Samir Shagavatov <span style=\" font-size:8pt; color:#00aa00;\">(For his help about translating algorithms a"
                        "nd other supports)</span></li>\n"
"<li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Roozbeh Pournader &amp; Mohammad Toossi <span style=\" font-size:8pt; color:#00aa00;\">(For their great code on converting Gregorian calendar to Jalali calendar and vice versa.)</span></li></ul>\n"
"<ul style=\"-qt-list-indent: 1;\"><li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Nigar Xiyavi, Lale Javanshir, S. Heydar Bayat, Isiq Sonmez, Xatire Ferecli &amp; ... <span style=\" font-size:8pt; color:#00aa00;\">(For their great support and feed back about AzConvert)</span></li>\n"
"<li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Haavard Nord, Eirik Chambre-Eng and their wive"
                        "s <span style=\" font-size:8pt; color:#00aa00;\">(For creating the wonderful C++ framework, Qt!)</span></li>\n"
"<li style=\" font-size:10pt;\" align=\"justify\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">You! <span style=\" font-size:8pt; color:#00aa00;\">(For using AzConvert)</span></li></ul></body></html>", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(AboutDialog);
    } // retranslateUi

};

namespace Ui {
    class AboutDialog: public Ui_AboutDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDIALOG_H
