/********************************************************************************
** Form generated from reading ui file 'addworddialog.ui'
**
** Created: Mon Sep 7 22:14:16 2009
**      by: Qt User Interface Compiler version 4.5.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ADDWORDDIALOG_H
#define UI_ADDWORDDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddWordDialog
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLineEdit *txtWord;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *txtEqual;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QRadioButton *rdbUser;
    QRadioButton *rdbSystem;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QPushButton *btnAdd;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnClose;

    void setupUi(QDialog *AddWordDialog)
    {
        if (AddWordDialog->objectName().isEmpty())
            AddWordDialog->setObjectName(QString::fromUtf8("AddWordDialog"));
        AddWordDialog->resize(359, 157);
        AddWordDialog->setModal(true);
        verticalLayout_4 = new QVBoxLayout(AddWordDialog);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(AddWordDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        txtWord = new QLineEdit(groupBox);
        txtWord->setObjectName(QString::fromUtf8("txtWord"));

        horizontalLayout->addWidget(txtWord);

        horizontalSpacer = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        txtEqual = new QLineEdit(groupBox);
        txtEqual->setObjectName(QString::fromUtf8("txtEqual"));

        horizontalLayout->addWidget(txtEqual);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rdbUser = new QRadioButton(groupBox);
        rdbUser->setObjectName(QString::fromUtf8("rdbUser"));
        rdbUser->setChecked(true);

        verticalLayout->addWidget(rdbUser);

        rdbSystem = new QRadioButton(groupBox);
        rdbSystem->setObjectName(QString::fromUtf8("rdbSystem"));

        verticalLayout->addWidget(rdbSystem);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        btnAdd = new QPushButton(groupBox);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setDefault(true);

        verticalLayout_2->addWidget(btnAdd);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(groupBox);

        verticalSpacer_3 = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        btnClose = new QPushButton(AddWordDialog);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));

        horizontalLayout_3->addWidget(btnClose);


        verticalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(AddWordDialog);
        QObject::connect(btnClose, SIGNAL(clicked()), AddWordDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddWordDialog);
    } // setupUi

    void retranslateUi(QDialog *AddWordDialog)
    {
        AddWordDialog->setWindowTitle(QApplication::translate("AddWordDialog", "Add word to dictionary", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("AddWordDialog", "Equals to:", 0, QApplication::UnicodeUTF8));
        rdbUser->setText(QApplication::translate("AddWordDialog", "Add to &user dictionary", 0, QApplication::UnicodeUTF8));
        rdbSystem->setText(QApplication::translate("AddWordDialog", "Add to &system dictionary", 0, QApplication::UnicodeUTF8));
        btnAdd->setText(QApplication::translate("AddWordDialog", "&Add", 0, QApplication::UnicodeUTF8));
        btnClose->setText(QApplication::translate("AddWordDialog", "&Close", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(AddWordDialog);
    } // retranslateUi

};

namespace Ui {
    class AddWordDialog: public Ui_AddWordDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDWORDDIALOG_H
