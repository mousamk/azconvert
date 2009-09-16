/********************************************************************************
** Form generated from reading ui file 'mainwindow.ui'
**
** Created: Mon Sep 7 22:14:16 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionExit;
    QAction *action_Latin_to_Arabic;
    QAction *action_Arabic_to_Latin;
    QAction *action_Cyrillic_to_Latin;
    QAction *action_ConvertText;
    QAction *action_Reload_dictionaries;
    QAction *action_Add_word_to_dictionary;
    QAction *actionCalendar_converter;
    QAction *action_Options;
    QAction *action_About;
    QAction *actionClear_All;
    QAction *actionAbout_Qt;
    QAction *action_LangEnglish;
    QAction *action_LangAzerbaijani;
    QAction *action_LangTurkish;
    QAction *action_LangAzTurkish;
    QAction *action_LangPersian;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_5;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QTextEdit *txtSource;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnNew;
    QPushButton *btnOpen;
    QPushButton *btnPaste;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *txtResult;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSave;
    QPushButton *btnCopy;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Convert;
    QMenu *menu_Tools;
    QMenu *menu_Language;
    QMenu *menu_Help;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(685, 543);
        QIcon icon;
        icon.addPixmap(QPixmap(QString::fromUtf8(":/res/AzConvert.ico")), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        action_Latin_to_Arabic = new QAction(MainWindow);
        action_Latin_to_Arabic->setObjectName(QString::fromUtf8("action_Latin_to_Arabic"));
        action_Latin_to_Arabic->setCheckable(true);
        action_Arabic_to_Latin = new QAction(MainWindow);
        action_Arabic_to_Latin->setObjectName(QString::fromUtf8("action_Arabic_to_Latin"));
        action_Arabic_to_Latin->setCheckable(true);
        action_Cyrillic_to_Latin = new QAction(MainWindow);
        action_Cyrillic_to_Latin->setObjectName(QString::fromUtf8("action_Cyrillic_to_Latin"));
        action_Cyrillic_to_Latin->setCheckable(true);
        action_ConvertText = new QAction(MainWindow);
        action_ConvertText->setObjectName(QString::fromUtf8("action_ConvertText"));
        QIcon icon1;
        icon1.addPixmap(QPixmap(QString::fromUtf8(":/res/player_rew.png")), QIcon::Normal, QIcon::Off);
        action_ConvertText->setIcon(icon1);
        action_Reload_dictionaries = new QAction(MainWindow);
        action_Reload_dictionaries->setObjectName(QString::fromUtf8("action_Reload_dictionaries"));
        action_Add_word_to_dictionary = new QAction(MainWindow);
        action_Add_word_to_dictionary->setObjectName(QString::fromUtf8("action_Add_word_to_dictionary"));
        QIcon icon2;
        icon2.addPixmap(QPixmap(QString::fromUtf8(":/res/AddWord.png")), QIcon::Normal, QIcon::Off);
        action_Add_word_to_dictionary->setIcon(icon2);
        actionCalendar_converter = new QAction(MainWindow);
        actionCalendar_converter->setObjectName(QString::fromUtf8("actionCalendar_converter"));
        QIcon icon3;
        icon3.addPixmap(QPixmap(QString::fromUtf8(":/res/Calendar.png")), QIcon::Normal, QIcon::Off);
        actionCalendar_converter->setIcon(icon3);
        action_Options = new QAction(MainWindow);
        action_Options->setObjectName(QString::fromUtf8("action_Options"));
        action_Options->setEnabled(false);
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        actionClear_All = new QAction(MainWindow);
        actionClear_All->setObjectName(QString::fromUtf8("actionClear_All"));
        QIcon icon4;
        icon4.addPixmap(QPixmap(QString::fromUtf8(":/res/Clear.png")), QIcon::Normal, QIcon::Off);
        actionClear_All->setIcon(icon4);
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        action_LangEnglish = new QAction(MainWindow);
        action_LangEnglish->setObjectName(QString::fromUtf8("action_LangEnglish"));
        action_LangEnglish->setText(QString::fromUtf8("English"));
        action_LangAzerbaijani = new QAction(MainWindow);
        action_LangAzerbaijani->setObjectName(QString::fromUtf8("action_LangAzerbaijani"));
        action_LangAzerbaijani->setText(QString::fromUtf8("Az\311\231rbaycanca"));
        action_LangTurkish = new QAction(MainWindow);
        action_LangTurkish->setObjectName(QString::fromUtf8("action_LangTurkish"));
        action_LangTurkish->setText(QString::fromUtf8("T\303\274rk\303\247e"));
        action_LangAzTurkish = new QAction(MainWindow);
        action_LangAzTurkish->setObjectName(QString::fromUtf8("action_LangAzTurkish"));
        action_LangAzTurkish->setText(QString::fromUtf8("\330\252\331\210\330\261\332\251\330\254\331\207"));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        action_LangAzTurkish->setFont(font);
        action_LangPersian = new QAction(MainWindow);
        action_LangPersian->setObjectName(QString::fromUtf8("action_LangPersian"));
        action_LangPersian->setText(QString::fromUtf8("\331\201\330\247\330\261\330\263\333\214"));
        action_LangPersian->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_5 = new QHBoxLayout(centralWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setMargin(5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_4 = new QHBoxLayout(frame);
        horizontalLayout_4->setSpacing(9);
        horizontalLayout_4->setMargin(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        txtSource = new QTextEdit(frame);
        txtSource->setObjectName(QString::fromUtf8("txtSource"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Tahoma"));
        font1.setPointSize(10);
        txtSource->setFont(font1);
        txtSource->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout->addWidget(txtSource);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btnNew = new QPushButton(frame);
        btnNew->setObjectName(QString::fromUtf8("btnNew"));

        horizontalLayout->addWidget(btnNew);

        btnOpen = new QPushButton(frame);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        horizontalLayout->addWidget(btnOpen);

        btnPaste = new QPushButton(frame);
        btnPaste->setObjectName(QString::fromUtf8("btnPaste"));
        btnPaste->setMinimumSize(QSize(71, 23));

        horizontalLayout->addWidget(btnPaste);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        txtResult = new QTextEdit(frame);
        txtResult->setObjectName(QString::fromUtf8("txtResult"));
        txtResult->setFont(font1);
        txtResult->setLayoutDirection(Qt::RightToLeft);
        txtResult->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout_2->addWidget(txtResult);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnSave = new QPushButton(frame);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_2->addWidget(btnSave);

        btnCopy = new QPushButton(frame);
        btnCopy->setObjectName(QString::fromUtf8("btnCopy"));

        horizontalLayout_2->addWidget(btnCopy);

        btnClear = new QPushButton(frame);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(75);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnClear->sizePolicy().hasHeightForWidth());
        btnClear->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(btnClear);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout_5->addWidget(frame);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 685, 22));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Convert = new QMenu(menu_File);
        menu_Convert->setObjectName(QString::fromUtf8("menu_Convert"));
        menu_Convert->setTearOffEnabled(false);
        menu_Tools = new QMenu(menuBar);
        menu_Tools->setObjectName(QString::fromUtf8("menu_Tools"));
        menu_Language = new QMenu(menu_Tools);
        menu_Language->setObjectName(QString::fromUtf8("menu_Language"));
        menu_Language->setEnabled(false);
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setIconSize(QSize(24, 24));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(txtSource, txtResult);
        QWidget::setTabOrder(txtResult, btnNew);
        QWidget::setTabOrder(btnNew, btnOpen);
        QWidget::setTabOrder(btnOpen, btnPaste);
        QWidget::setTabOrder(btnPaste, btnSave);
        QWidget::setTabOrder(btnSave, btnCopy);
        QWidget::setTabOrder(btnCopy, btnClear);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Tools->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(menu_Convert->menuAction());
        menu_File->addSeparator();
        menu_File->addAction(actionExit);
        menu_Convert->addAction(action_Latin_to_Arabic);
        menu_Convert->addAction(action_Arabic_to_Latin);
        menu_Convert->addAction(action_Cyrillic_to_Latin);
        menu_Tools->addAction(action_ConvertText);
        menu_Tools->addAction(action_Reload_dictionaries);
        menu_Tools->addAction(action_Add_word_to_dictionary);
        menu_Tools->addSeparator();
        menu_Tools->addAction(actionCalendar_converter);
        menu_Tools->addSeparator();
        menu_Tools->addAction(action_Options);
        menu_Tools->addAction(menu_Language->menuAction());
        menu_Language->addAction(action_LangEnglish);
        menu_Language->addAction(action_LangAzerbaijani);
        menu_Language->addAction(action_LangTurkish);
        menu_Language->addAction(action_LangAzTurkish);
        menu_Language->addAction(action_LangPersian);
        menu_Help->addAction(action_About);
        menu_Help->addAction(actionAbout_Qt);
        mainToolBar->addAction(actionClear_All);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCalendar_converter);
        mainToolBar->addAction(action_Add_word_to_dictionary);
        mainToolBar->addSeparator();
        mainToolBar->addAction(action_ConvertText);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "AzConvert", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        action_Latin_to_Arabic->setText(QApplication::translate("MainWindow", "&1) Latin to Arabic", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Latin_to_Arabic->setToolTip(QApplication::translate("MainWindow", "Latin script to Arabic script convert mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Latin_to_Arabic->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", 0, QApplication::UnicodeUTF8));
        action_Arabic_to_Latin->setText(QApplication::translate("MainWindow", "&2) Arabic to Latin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Arabic_to_Latin->setToolTip(QApplication::translate("MainWindow", "Arabic script to Latin script convert mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Arabic_to_Latin->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", 0, QApplication::UnicodeUTF8));
        action_Cyrillic_to_Latin->setText(QApplication::translate("MainWindow", "&3) Cyrillic to Latin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action_Cyrillic_to_Latin->setToolTip(QApplication::translate("MainWindow", "Cyrillic script to Latin script convert mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action_Cyrillic_to_Latin->setShortcut(QApplication::translate("MainWindow", "Ctrl+3", 0, QApplication::UnicodeUTF8));
        action_ConvertText->setText(QApplication::translate("MainWindow", "&Convert", 0, QApplication::UnicodeUTF8));
        action_ConvertText->setShortcut(QApplication::translate("MainWindow", "F9", 0, QApplication::UnicodeUTF8));
        action_Reload_dictionaries->setText(QApplication::translate("MainWindow", "&Reload dictionaries", 0, QApplication::UnicodeUTF8));
        action_Reload_dictionaries->setShortcut(QApplication::translate("MainWindow", "F5", 0, QApplication::UnicodeUTF8));
        action_Add_word_to_dictionary->setText(QApplication::translate("MainWindow", "&Add word...", 0, QApplication::UnicodeUTF8));
        action_Add_word_to_dictionary->setShortcut(QApplication::translate("MainWindow", "F4", 0, QApplication::UnicodeUTF8));
        actionCalendar_converter->setText(QApplication::translate("MainWindow", "Calen&dar switch...", 0, QApplication::UnicodeUTF8));
        actionCalendar_converter->setShortcut(QApplication::translate("MainWindow", "F6", 0, QApplication::UnicodeUTF8));
        action_Options->setText(QApplication::translate("MainWindow", "&Options...", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About...", 0, QApplication::UnicodeUTF8));
        actionClear_All->setText(QApplication::translate("MainWindow", "Clear All", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionClear_All->setToolTip(QApplication::translate("MainWindow", "Clear both boxes", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionClear_All->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("MainWindow", "About &Qt...", 0, QApplication::UnicodeUTF8));
        btnNew->setText(QApplication::translate("MainWindow", "&New", 0, QApplication::UnicodeUTF8));
        btnOpen->setText(QApplication::translate("MainWindow", "&Open...", 0, QApplication::UnicodeUTF8));
        btnPaste->setText(QApplication::translate("MainWindow", "&Paste", 0, QApplication::UnicodeUTF8));
        btnSave->setText(QApplication::translate("MainWindow", "&Save...", 0, QApplication::UnicodeUTF8));
        btnCopy->setText(QApplication::translate("MainWindow", "&Copy", 0, QApplication::UnicodeUTF8));
        btnClear->setText(QApplication::translate("MainWindow", "Cle&ar", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Convert->setTitle(QApplication::translate("MainWindow", "&Convert", 0, QApplication::UnicodeUTF8));
        menu_Tools->setTitle(QApplication::translate("MainWindow", "&Tools", 0, QApplication::UnicodeUTF8));
        menu_Language->setTitle(QApplication::translate("MainWindow", "&Language", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
