#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "l2aconversion.h"
#include "c2lconversion.h"
#include "a2lconversion.h"



enum ConvertMode
{
    L2A = 0,
    A2L,
    C2L
};


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

private:
    //void SetupConnections();
    void InitData();
    void SetModeDirection();


public:
    ConvertMode cMode;

private:
    Ui::MainWindow *ui;
    L2AConversion* l2aEngine;
    C2LConversion* c2lEngine;
    A2LConversion* a2lEngine;


private slots:
    void on_actionCalendar_converter_triggered();
    void on_action_Add_word_to_dictionary_triggered();
    void on_btnClear_clicked();
    void on_action_About_triggered();
    void on_actionAbout_Qt_triggered();
    void on_actionClear_All_triggered();
    void on_btnSave_clicked();
    void on_btnOpen_clicked();
    void on_btnCopy_clicked();
    void on_btnPaste_clicked();
    void on_btnNew_clicked();
    void on_action_Reload_dictionaries_triggered();
    void on_action_Cyrillic_to_Latin_triggered();
    void on_action_Arabic_to_Latin_triggered();
    void on_action_Latin_to_Arabic_triggered();
    void on_action_ConvertText_triggered();
    void on_actionExit_triggered();
};

#endif // MAINWINDOW_H
