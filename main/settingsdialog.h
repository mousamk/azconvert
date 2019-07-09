#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QtWidgets/QDialog>
#include <QMap>

#include "charreplacerecord.h"


namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    

public:
    explicit SettingsDialog(QMap<int, CharReplaceRecord>& replaceChars, QWidget *parent = 0);
    ~SettingsDialog();


private:
    bool saveSettings();
    

private slots:
    void on_chkLDiacritics_clicked();
    void on_btnCancel_clicked();
    void on_btnOk_clicked();


private:
    Ui::SettingsDialog *ui;
    QMap<int, CharReplaceRecord>& replaceChars;
};

#endif // SETTINGSDIALOG_H
