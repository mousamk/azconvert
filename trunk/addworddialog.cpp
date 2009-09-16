#include <QMessageBox>
#include <QFile>

#include "addworddialog.h"



AddWordDialog::AddWordDialog(QWidget *parent) :
    QDialog(parent){
    m_ui.setupUi(this);
}

AddWordDialog::AddWordDialog(MainWindow* main, QString word, QWidget* parent) :
        QDialog(parent),
        mainWindow(main)
{
    m_ui.setupUi(this);


    word = word.trimmed();
    m_ui.txtWord->setText(word);

    isL2A = mainWindow->cMode == L2A;

    if (isL2A)
    {
        m_ui.txtWord->setLayoutDirection(Qt::LeftToRight);
        m_ui.txtEqual->setLayoutDirection(Qt::RightToLeft);
    }
    else
    {
        m_ui.txtWord->setLayoutDirection(Qt::RightToLeft);
        m_ui.txtEqual->setLayoutDirection(Qt::LeftToRight);
    }

    m_ui.txtWord->setFocus();
    m_ui.txtWord->selectAll();
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
    QString str;
    if (isL2A)
        m_ui.txtEqual->setText(Standardize(m_ui.txtEqual->text()));
    else
        m_ui.txtWord->setText(Standardize(m_ui.txtWord->text()));

    QString fileName("");
    if (m_ui.rdbUser->isChecked())
    {
        if (isL2A)
            fileName = "./dicts/dict_AzL2AzA_user.dat";
        else
            fileName = "./dicts/dict_AzA2AzL_user.dat";
    }
    else if (m_ui.rdbSystem->isChecked())
    {
        if (isL2A)
            fileName = "./dicts/dict_AzL2AzA.dat";
        else
            fileName = "./dicts/dict_AzA2AzL.dat";
    }

    QFile file(fileName);
    bool fatal = false;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        str = QString::fromUtf8(file.readAll());
        file.close();
    }
    else if (file.error() == QFile::OpenError)
    {
        //QMessageBox::warning(mainWindow, tr("File"), tr("Error opening file"), tr("OK"));

        //The file doesn't exist, so create it:
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            file.write(QString("").toUtf8());
            file.close();
        }
        else
        {
            QMessageBox::warning(mainWindow, tr("File"), tr("Error writing file"), tr("OK"));
            fatal = true;
        }
    }

    if (!fatal)
    {
        QString newExp = "[" + m_ui.txtWord->text().trimmed() + "]";
        if (!str.contains(newExp, Qt::CaseSensitive))
        {
            QString str5 = "=" + m_ui.txtEqual->text().trimmed() + "\r\n";
            QString str6 = "=" + m_ui.txtEqual->text().trimmed() + "\n";
            if (str.contains(str5) || str.contains(str6))
            {
                int index;
                if (str.contains(str5))
                    index = str.indexOf(str5);
                else
                    index = str.indexOf(str6);
                while(str[index] != ']')
                    index--;
                index++;

                QString str7 = "[" + m_ui.txtWord->text().trimmed() + "]";
                str.insert(index, str7);

                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    file.write(str.toUtf8());
                    file.close();
                }
                else
                {
                    QMessageBox::warning(mainWindow, tr("File"), tr("Error writing file"), tr("OK"));
                    fatal = true;
                }
            }
            else
            {
                QString str8("");
                if (!str.endsWith("\n"))
                    str8 = "\n";
                str8 += "[" + m_ui.txtWord->text().trimmed() + "]\t\t=" + m_ui.txtEqual->text().trimmed() + "\n";
                if (file.open(QIODevice::Append | QIODevice::Text))
                {
                    file.write(str8.toUtf8());
                    file.close();
                }
                else
                {
                    QMessageBox::warning(mainWindow, tr("File"), tr("Error writing file"), tr("OK"));
                    fatal = true;
                }
            }

            this->accept();
        }
        else
        {
            int length = str.indexOf(newExp);
            while (str[length] != '=')
                length++;
            length++;
            int num2 = length;
            QString str4("");
            while (num2 < str.length() && str[num2] != '\r' && (str[num2] != '\n'))
            {
                str4 = str4 + QString(str[num2]);
                num2++;
            }
            if (str4 == m_ui.txtEqual->text().trimmed())
            {
                //MessageBox.Show("The word and the equivalent already exists in the dictionary!");
                QMessageBox::information(mainWindow, tr("Word"), tr("The word and the equivalent already exists in the dictionary!"), tr("OK"));
            }
            else //if (MessageBox.Show("The word already exists in the dictionary, but the available equivalent doesn't match with your word!\nDo you want to update that? Otherwise the existing word will be saved.", "What to do?", MessageBoxButtons.YesNo, MessageBoxIcon.Question, MessageBoxDefaultButton.Button2) != DialogResult.No)
            {
                if (QMessageBox::Yes == QMessageBox::question(mainWindow, tr("Replace"), tr("The word already exists in the dictionary, but the available equivalent doesn't match with your word!\nDo you want to update that? Otherwise the existing word will be saved."), QMessageBox::Yes | QMessageBox::No, QMessageBox::No))
                {
                    while (num2 < str.length() && (str[num2] == '\r' || str[num2] == '\n'))
                        num2--;

                    str = str.mid(0, length) + m_ui.txtEqual->text().trimmed() + str.mid(++num2);
                    if (!str.endsWith("\n"))
                        str += "\r\n";

                    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                    {
                        file.write(str.toUtf8());
                        file.close();
                    }
                    else
                    {
                        QMessageBox::warning(mainWindow, tr("File"), tr("Error writing file"), tr("OK"));
                        fatal = true;
                    }
                }
            }

            this->accept();
        }
    }
}


QString AddWordDialog::Standardize(QString w)
{
    w.replace(QChar('\x43', '\x06'), QChar('\xa9', '\x06'));
    w.replace(QChar('\x4a', '\x06'), QChar('\xcc', '\x06'));
    w.replace(QChar('\x2b', '\x20'), QChar('\x0c', '\x20'));
    return w;
}











