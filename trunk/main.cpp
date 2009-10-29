#include <QtGui/QApplication>
#include <QTextCodec>
//#include <QTranslator>

#include "mainwindow.h"
//#include "mydata.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    /*QTranslator translator;
    translator.load("azconvert_fa.qm");
    a.installTranslator(&translator);*/

    MainWindow w;
    w.show();

    return a.exec();
}
