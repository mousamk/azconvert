#include <QtWidgets/QMessageBox>
#include <QFile>
#include <QDir>
#include <QHash>
#include <QTranslator>

#include "addworddialog.h"
#include "convertor.h"
#include "util.h"
#include "dbservice.h"
#include "settings.h"



AddWordDialog::AddWordDialog(QWidget *parent) :
    QDialog(parent){
    m_ui.setupUi(this);
}

AddWordDialog::AddWordDialog(MainWindow* main, QString word, QWidget* parent) :
        QDialog(parent),
        mainWindow(main)
{
    m_ui.setupUi(this);


    //Preprocessing the word:
    word = word.trimmed();
    WORD_TO_LOWER(word, word);

    //Setting the word to the text box:
    m_ui.txtWord->setText(word);

    //Setting text box layouts:
    Convertor* convertor = mainWindow->getConvertor();
    m_ui.txtWord->setLayoutDirection(convertor->getSourceLayoutDirection());
    m_ui.txtEqual->setLayoutDirection(convertor->getDestinationLayoutDirection());

    //focus and select word:
    m_ui.txtWord->setFocus();
    m_ui.txtWord->selectAll();

    //Retranslate UI:
    //TRANSLATE_MUI(Settings::GetInstance(this->parent())->getLanguage());
    //m_ui.retranslateUi(this);
}


void AddWordDialog::changeEvent(QEvent *e)
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

void AddWordDialog::on_btnAdd_clicked()
{
    //TODO: Validate word

    QString word = m_ui.txtWord->text();
    QString lWord;
    WORD_TO_LOWER(word, lWord);
    QString equal = m_ui.txtEqual->text();

    Convertor* convertor = mainWindow->getConvertor();
    QHash<QString,QString> words = convertor->getWords();
    bool success = true;

    //Check if it already exists:
    if (words.contains(lWord))
    {
        QString oldEqual = words.value(lWord);

        //Check if it already exists with the same equivalent:
        if (oldEqual.compare(equal) == 0)
        {
            QMessageBox::information(this, tr("Already exists"), tr("The same word with the same equivalent already exists in database."));
            this->accept();
        }
        else
        {
            //Ask if user wants to update the equivalent:
            int res = QMessageBox::question(this, tr("Another equivalent"), tr("The word with another equivalent (<b>%1</b>) already exists in database. Do you want to change it?").arg(oldEqual), QMessageBox::Yes, QMessageBox::No);
            if(QMessageBox::Yes == res)
            {
                success = DbService::getInstance()->updateWord(convertor->getTablesPostfix(), word, equal);
                if(success)
                {
                    words[lWord] = equal;
                    this->accept();
                }
            }
            else
            {
                this->accept();
            }
        }
    }
    else
    {
        //Add to db:
        success = DbService::getInstance()->addWord(convertor->getTablesPostfix(), word, equal);
        if (success)
        {
            words.insert(word, equal);
            this->accept();
        }
    }

    if (!success)
        QMessageBox::warning(this, tr("Not successful"), tr("An error happened and the operation was unsuccessful!"));
}


QString AddWordDialog::Standardize(QString w)
{
    w.replace(QChar('\x43', '\x06'), QChar('\xa9', '\x06'));
    w.replace(QChar('\x4a', '\x06'), QChar('\xcc', '\x06'));
    w.replace(QChar('\x2b', '\x20'), QChar('\x0c', '\x20'));
    return w;
}











