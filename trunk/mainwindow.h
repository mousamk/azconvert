#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QLabel>

#include "convertor.h"
#include "util.h"



namespace Ui
{
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Convertor* getConvertor();


public slots:
    void newVersionAvailable(QString version);
    
    
protected:
	void resizeEvent(QResizeEvent*);
    

private:
    void SetModeDirection();
	void showFlashInfo(const QString&);


signals:
	void windowResized(QResizeEvent*);


private slots:
    void on_actionWikipediaMode_triggered();
    void on_actionCalendar_converter_triggered();
    void on_action_Add_word_to_dictionary_triggered();
    void on_action_About_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionClear_All_triggered();
    void on_btnSave_clicked();
    void on_btnOpen_clicked();
    void on_btnCopy_clicked();
    void on_btnPaste_clicked();
    void on_action_Reload_dictionaries_triggered();
    void on_action_Cyrillic_to_Latin_triggered();
    void on_action_Arabic_to_Latin_triggered();
    void on_action_Latin_to_Arabic_triggered();
    void on_action_ConvertText_triggered();
	void updateInfoLabelPosition(QResizeEvent*);
	void checkForUpdate();
	void handleFlashUrlClick(const QString&);
    void on_action_LangAzTurkish_triggered();
    void on_action_LangEnglish_triggered();
    void on_action_LangAzerbaijani_triggered();


private:
    Ui::MainWindow *ui;
	QLabel* infoLabel;
	//QString infoLabelUrl;
    Convertor* convertor;
};

#endif // MAINWINDOW_H
