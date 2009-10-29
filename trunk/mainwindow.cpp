#include <QProgressDialog>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include <QFile>

#include "settings.h"
#include "mainwindow.h"
#include "addworddialog.h"
#include "calendarswitchdialog.h"
#include "ui_mainwindow.h"
#include "ui_aboutdialog.h"
#include "l2aconversion.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->mainToolBar->setVisible(false);
    //ui->action_ConvertText->setIcon(QIcon(":/res/Convert.ico"));
    on_action_Latin_to_Arabic_triggered();

    InitData();
    SetModeDirection();

    //Load settings:
    ui->actionWikipediaMode->setChecked(Settings::GetInstance()->GetWikiMode());
}

MainWindow::~MainWindow()
{
    delete l2aEngine;
    delete ui;
}


/*void MainWindow::SetupConnections()
{
    connect(ui->actionExit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
}*/


void MainWindow::on_actionExit_triggered()
{
    qApp->quit();
}


void MainWindow::InitData()
{
    cMode = L2A;
    l2aEngine = new L2AConversion();
    c2lEngine = new C2LConversion();
    a2lEngine = new A2LConversion();
}


void MainWindow::on_action_ConvertText_triggered()
{
    setCursor(Qt::WaitCursor);

    QProgressDialog *progress = new QProgressDialog(tr("Converting..."), tr("Cancel"), 0, ui->txtSource->toPlainText().length(), this);
    progress->setWindowModality(Qt::WindowModal);
    progress->show();

    switch(cMode)
    {
        case L2A:
            l2aEngine->SetOriginalText(ui->txtSource->toPlainText());
            ui->txtResult->document()->setPlainText(l2aEngine->Convert(progress));
            /*l2aEngine->SetOriginalText(ui->txtSource->toHtml());
            ui->txtResult->document()->setHtml(l2aEngine->ConvertHtml());*/
            break;
        case A2L:
            a2lEngine->SetOriginalText(ui->txtSource->toPlainText());
            ui->txtResult->document()->setPlainText(a2lEngine->Convert(progress));
            break;
        case C2L:
            QString str = c2lEngine->Convert(ui->txtSource->toPlainText());
            ui->txtResult->document()->setPlainText(str);
            break;
    }

    progress->close();

    setCursor(Qt::ArrowCursor);
}

void MainWindow::on_action_Latin_to_Arabic_triggered()
{
    cMode = L2A;

    ui->action_Arabic_to_Latin->setChecked(false);
    ui->action_Latin_to_Arabic->setChecked(true);
    ui->action_Cyrillic_to_Latin->setChecked(false);

    ui->action_Add_word_to_dictionary->setEnabled(true);

    SetModeDirection();
}

void MainWindow::on_action_Arabic_to_Latin_triggered()
{
    cMode = A2L;

    ui->action_Arabic_to_Latin->setChecked(true);
    ui->action_Latin_to_Arabic->setChecked(false);
    ui->action_Cyrillic_to_Latin->setChecked(false);

    ui->action_Add_word_to_dictionary->setEnabled(true);

    SetModeDirection();
}


void MainWindow::on_action_Cyrillic_to_Latin_triggered()
{
    cMode = C2L;

    ui->action_Arabic_to_Latin->setChecked(false);
    ui->action_Latin_to_Arabic->setChecked(false);
    ui->action_Cyrillic_to_Latin->setChecked(true);

    ui->action_Add_word_to_dictionary->setEnabled(false);

    SetModeDirection();
}


void MainWindow::SetModeDirection()
{
    if (cMode == L2A || cMode == C2L)
    {
        /*ui->frame->setLayoutDirection(Qt::LeftToRight);
        ui->btnConvert->setText(tr("==>"));
        ui->txtResult->setLayoutDirection(Qt::RightToLeft);*/
        ui->txtSource->setLayoutDirection(Qt::LeftToRight);
        if (cMode == L2A)
            ui->txtResult->setLayoutDirection(Qt::RightToLeft);
        else
            ui->txtResult->setLayoutDirection(Qt::LeftToRight);
    }
    else if (cMode == A2L)
    {
        ui->txtSource->setLayoutDirection(Qt::RightToLeft);
        ui->txtResult->setLayoutDirection(Qt::LeftToRight);
    }
}


void MainWindow::on_action_Reload_dictionaries_triggered()
{
    if (cMode == L2A)
        l2aEngine->OpenDicts();
    else if (cMode == A2L)
        a2lEngine->OpenDicts();
}

void MainWindow::on_btnNew_clicked()
{
    ui->txtSource->clear();
    ui->txtSource->setFocus();
}

void MainWindow::on_btnPaste_clicked()
{
    QClipboard* clip = QApplication::clipboard();
    ui->txtSource->document()->setPlainText(clip->text(QClipboard::Clipboard));
}

void MainWindow::on_btnCopy_clicked()
{
    QClipboard* clip = QApplication::clipboard();
    clip->setText(ui->txtResult->document()->toPlainText());
}

void MainWindow::on_btnOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->txtSource->setPlainText(QString::fromUtf8(file.readAll()));
        statusBar()->showMessage(tr("File successfully loaded."), 3000);
    }
}

void MainWindow::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(ui->txtResult->toPlainText().toUtf8());
        statusBar()->showMessage(tr("File saved successfully."), 3000);
    }
}

void MainWindow::on_actionClear_All_triggered()
{
    ui->txtResult->clear();
    ui->txtSource->clear();
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QApplication::aboutQt();
}

void MainWindow::on_action_About_triggered()
{
    Ui::AboutDialog* base = new Ui::AboutDialog();
    QDialog* dlg = new QDialog(this, Qt::MSWindowsFixedSizeDialogHint);
    base->setupUi(dlg);
    dlg->show();
}

void MainWindow::on_btnClear_clicked()
{
    ui->txtResult->clear();
}

void MainWindow::on_action_Add_word_to_dictionary_triggered()
{
    QString word("");
    if (ui->txtSource->textCursor().hasSelection())
        word = ui->txtSource->textCursor().selectedText();
    AddWordDialog* dlg = new AddWordDialog(this, word, this);
    dlg->show();
}

void MainWindow::on_actionCalendar_converter_triggered()
{
    CalendarSwitchDialog* dlg = new CalendarSwitchDialog(this);
    dlg->show();
}

void MainWindow::on_actionWikipediaMode_triggered()
{
    bool check = ui->actionWikipediaMode->isChecked();
    Settings::GetInstance()->SetWikiMode(check);

    //Show information:
    if (check)
    {
        QMessageBox::information(this, tr("Wikipedia mode"), tr("This mode is for transliterating Azerbaijani wikipedia's articles."
                                                                "\nIn this mode, AzConvert automatically knows WikiMedia's formats and considers them in tranliteration."
                                                                "\n\nIt's not perfect yet and still is in development."), tr("Ok"));
    }
}
