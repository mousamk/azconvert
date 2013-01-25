#ifndef ADDWORDDIALOG_H
#define ADDWORDDIALOG_H

#include <QString>

#include "ui_addworddialog.h"
#include "mainwindow.h"


class AddWordDialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(AddWordDialog)

public:
    explicit AddWordDialog(QWidget *parent = 0);
    AddWordDialog(MainWindow* main, QString word, QWidget* parent = 0);

protected:
    virtual void changeEvent(QEvent *e);
    QString Standardize(QString);

private:
    Ui::AddWordDialog m_ui;
    MainWindow* mainWindow;

private slots:
    void on_btnAdd_clicked();
};

#endif // ADDWORDDIALOG_H
