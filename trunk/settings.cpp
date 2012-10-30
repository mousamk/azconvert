#include <QSettings>
#include <QDebug>

#include "settings.h"
#include "config.h"


//Allocate memory for static member variables:
Settings* Settings::instance = NULL;


Settings::Settings(QObject* parent)
	: QObject(parent)
{
	//Load changable settings:
    LoadSettings();
}


Settings* Settings::GetInstance(QObject* parent)
{
    if (instance == NULL)
		instance = new Settings(parent);

    return instance;
}


bool Settings::getWikiMode() const
{
    return wikiMode;
}


void Settings::setWikiMode(bool mode)
{
    wikiMode = mode;
	settings.setValue("wikimode", wikiMode);
}


bool Settings::getUpdateCheck() const
{
	return updateCheck;
}


void Settings::setUpdateCheck(bool check)
{
	updateCheck = check;
	settings.setValue("updatecheck", updateCheck);
}


QString Settings::getLanguage() const
{
    qDebug() << "lang is: " << language;
    return language;
}


void Settings::setLanguage(QString lang)
{
    language = lang;
    settings.setValue("language", language);
    qDebug() << "lang saved to " << language;
}


void Settings::LoadSettings()
{
	//Read each setting:
    wikiMode = settings.value("wikimode", false).toBool();
	updateCheck = settings.value("updatecheck", true).toBool();
    language = settings.value("language", "en_US").toString();
    //qDebug() << "lang is:" << language;
}


/*void Settings::SaveSettings()
{
	//Save each setting:
    settings.setValue("wikimode", wikiMode);
	settings.setValue("updatecheck", updateCheck);
}*/
