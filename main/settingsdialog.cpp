#include <QtWidgets/QMessageBox>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settings.h"
#include "dbservice.h"


SettingsDialog::SettingsDialog(QMap<int, CharReplaceRecord>& replaceChars, QWidget *parent) :
    replaceChars(replaceChars),
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    //Load form info:
    ui->chkLDiacritics->setChecked(Settings::GetInstance()->getEnableDiacritics());
    ui->lstDetailedDiacritics->clear();

    QMap<int, CharReplaceRecord>::const_iterator i;
    QListWidgetItem* item;
    for(i = replaceChars.begin(); i != replaceChars.end(); i++)
    {
        CharReplaceRecord temp = i.value();
        item = new QListWidgetItem(temp.source + " => " + temp.equivalent);
        item->setData(2001, temp.id);
        item->setCheckState(temp.enabled ? Qt::Checked : Qt::Unchecked);
        ui->lstDetailedDiacritics->addItem(item);
    }
}


SettingsDialog::~SettingsDialog()
{
    delete ui;
}


void SettingsDialog::on_chkLDiacritics_clicked()
{
    ui->lstDetailedDiacritics->setEnabled(ui->chkLDiacritics->isChecked());
    Settings::GetInstance()->setEnableDiacritics(ui->chkLDiacritics->isChecked());
}


void SettingsDialog::on_btnCancel_clicked()
{
    this->reject();
}


bool SettingsDialog::saveSettings()
{
    QListWidgetItem* item;
    bool ok = true;
    for(int i=0; i<ui->lstDetailedDiacritics->count(); i++)
    {
        item = ui->lstDetailedDiacritics->item(i);
        int id = item->data(2001).toInt();
        bool checked = item->checkState() == Qt::Checked;
        if (checked != replaceChars[id].enabled)
        {
            replaceChars[id].enabled = item->checkState() == Qt::Checked;
            ok = ok && DbService::getInstance()->updateReplaceChar("a", id, checked);
        }
    }

    return ok;
}


void SettingsDialog::on_btnOk_clicked()
{
    if(!saveSettings())
        QMessageBox::critical(this, tr("Error"), tr("There was a problem saving your settings!"), QMessageBox::Ok);
    else
        this->accept();
}
