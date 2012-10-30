#include <QProgressDialog>
#include <QDesktopServices>
#include <QMessageBox>
#include <QClipboard>
#include <QFileDialog>
#include <QTimer>
#include <QFile>
#include <QDebug>
#include <QResizeEvent>
#include <QTranslator>

#include "settings.h"
#include "mainwindow.h"
#include "addworddialog.h"
#include "calendarswitchdialog.h"
#include "ui_mainwindow.h"
#include "ui_aboutdialog.h"
#include "l2aconversion.h"
#include "a2lconversion.h"
#include "c2lconversion.h"
#include "update.h"
#include "dbservice.h"
#include "config.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    QTranslator translator;
    translator.load(QString("../../trunk/azconvert_") + LANG + QString(".qm"));
    QApplication::instance()->installTranslator(&translator);
    this->setLayoutDirection(tr("LTR") == "LTR" ? Qt::LeftToRight : Qt::RightToLeft);
    m_ui.retranslateUi(this);

	ui->setupUi(this);
	infoLabel = new QLabel(this);
	infoLabel->setGeometry(0, 0, 0, 0);
    
    //Initialize db:
    if (!DbService::createInstance(this))
    {
        QMessageBox::critical(this, tr("Database Error"), "An error happened loading database."
                              "\nThe Database is crucial for AzConvert to work."
                              "\n\nReinstalling application may help."
                              " If even by reinstalling this error occurred again, please contact the developer.", QMessageBox::Ok);
        this->close();
    }
    
    //Set initial mode to L2A:
    on_action_Latin_to_Arabic_triggered();

	//Setup connections:
	connect(infoLabel, SIGNAL(linkActivated(const QString&)), this, SLOT(handleFlashUrlClick(const QString&)), Qt::UniqueConnection);
	connect(this, SIGNAL(windowResized(QResizeEvent*)), this, SLOT(updateInfoLabelPosition(QResizeEvent*)), Qt::UniqueConnection);

    SetModeDirection();

    //Load settings:
    ui->actionWikipediaMode->setChecked(Settings::GetInstance(this)->getWikiMode());

	//Check for update:
	if (Settings::GetInstance(this)->getUpdateCheck())
    {
        connect(Update::getInstance(this->parent()), SIGNAL(newVersionAvailable(QString)), SLOT(newVersionAvailable(QString)));
		QTimer::singleShot(10000, this, SLOT(checkForUpdate()));
    }

    //Retranslate ui:
    //TRANSLATE(Settings::GetInstance(this)->getLanguage());
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_ConvertText_triggered()
{
    setCursor(Qt::WaitCursor);

    QProgressDialog *progress = new QProgressDialog(tr("Converting..."), tr("Cancel"), 0, ui->txtSource->toPlainText().length(), this);
    progress->setWindowModality(Qt::WindowModal);
    progress->show();

    //TODO: Get the proper wiki mode:
    bool wikiMode = Settings::GetInstance(this)->getWikiMode();
    //qDebug() << "org text:" << ui->txtSource->toPlainText();
    convertor->setOriginalText(ui->txtSource->toPlainText());
    ui->txtResult->document()->setPlainText(convertor->convert(progress, wikiMode));
    //qDebug() << "res text:" << convertor->getConvertedResult();
    
    progress->close();
    setCursor(Qt::ArrowCursor);
}

void MainWindow::on_action_Latin_to_Arabic_triggered()
{
    convertor = new L2AConversion(this);

    ui->action_Arabic_to_Latin->setChecked(false);
    ui->action_Latin_to_Arabic->setChecked(true);
    ui->action_Cyrillic_to_Latin->setChecked(false);

    ui->action_Add_word_to_dictionary->setEnabled(true);

    SetModeDirection();
}

void MainWindow::on_action_Arabic_to_Latin_triggered()
{
    convertor = new A2LConversion(this);

    ui->action_Arabic_to_Latin->setChecked(true);
    ui->action_Latin_to_Arabic->setChecked(false);
    ui->action_Cyrillic_to_Latin->setChecked(false);

    ui->action_Add_word_to_dictionary->setEnabled(true);

    SetModeDirection();
}


void MainWindow::on_action_Cyrillic_to_Latin_triggered()
{
    convertor = new C2LConversion(this);

    ui->action_Arabic_to_Latin->setChecked(false);
    ui->action_Latin_to_Arabic->setChecked(false);
    ui->action_Cyrillic_to_Latin->setChecked(true);

    ui->action_Add_word_to_dictionary->setEnabled(false);

    SetModeDirection();
}


void MainWindow::SetModeDirection()
{
    ui->txtSource->setLayoutDirection(convertor->getSourceLayoutDirection());
    ui->txtResult->setLayoutDirection(convertor->getDestinationLayoutDirection());
}


void MainWindow::on_action_Reload_dictionaries_triggered()
{
    convertor->reloadResources(true);
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
        //statusBar()->showMessage(tr("File successfully loaded."), 3000);
    }
}


void MainWindow::on_btnSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(ui->txtResult->toPlainText().toUtf8());
        //statusBar()->showMessage(tr("File saved successfully."), 3000);
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
    Settings::GetInstance(this)->setWikiMode(check);
}


void MainWindow::checkForUpdate()
{
    Update::getInstance(this->parent())->checkForUpdate();
}


void MainWindow::showFlashInfo(const QString &message)
{
	//Configure info label:
	infoLabel->setGeometry(this->width()-210, 0, 200, 20);
	infoLabel->setStyleSheet("background-color: #FFFF44;");
	infoLabel->setText(message);
    infoLabel->setToolTip(message);
	infoLabel->show();
}


void MainWindow::handleFlashUrlClick(const QString &url)
{
	//Construct url object:
	QUrl togoUrl(url);

	//Check if it's not valid:
	if (!togoUrl.isValid())
		qDebug() << "Invalid url: " << url;
	else
	{
		//Open the url in browser:
		if (!QDesktopServices::openUrl(togoUrl))
			qDebug() << "Going to url " << url << " was not successful!";
	}
}


void MainWindow::newVersionAvailable(QString version)
{
    showFlashInfo("&nbsp; <a href=\"" + QString(APP_HOMEPAGE) + "\">New Versian " + version + " is Available!</a>");
}


Convertor* MainWindow::getConvertor()
{
    return convertor;
}


void MainWindow::updateInfoLabelPosition(QResizeEvent*)
{
	//Update info label's position:
	if (infoLabel->isVisible())
		infoLabel->setGeometry(this->width()-210, 0, 200, 20);
}


void MainWindow::resizeEvent(QResizeEvent*e)
{
	//call the base method:
	QMainWindow::resizeEvent(e);

	emit windowResized(e);
}


void MainWindow::on_action_LangAzTurkish_triggered()
{
    TRANSLATE("az_IR");
    Settings::GetInstance(this)->setLanguage("az_IR");
}


void MainWindow::on_action_LangEnglish_triggered()
{
    TRANSLATE("en_US");
    Settings::GetInstance(this)->setLanguage("en_US");
    //ui->retranslateUi(this);
}


void MainWindow::on_action_LangAzerbaijani_triggered()
{
    TRANSLATE("az_AZ");
    Settings::GetInstance(this)->setLanguage("az_AZ");
}
