#ifndef CALENDARSWITCHDIALOG_H
#define CALENDARSWITCHDIALOG_H

#include "ui_calendarswitchdialog.h"

class CalendarSwitchDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(CalendarSwitchDialog)

public:
    explicit CalendarSwitchDialog(QWidget *parent = 0);


private:
    void FillAzerbaijaniMonthesBox();


protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::CalendarSwitchDialog m_ui;

private slots:
    void on_btnJa2Gr_clicked();
    void on_btnGr2Ja_clicked();
    void on_chkAzMonthes_stateChanged(int );
};

#endif // CALENDARSWITCHDIALOG_H
