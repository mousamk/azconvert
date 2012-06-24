#include <QSettings>
#include "settings.h"


Settings* Settings::instance = NULL;

Settings::Settings(QObject* parent)
	: QObject(parent)
{
	//Load changable settings:
    LoadSettings();

	//Load static values:
	initReadOnlySettings();
}

void Settings::initReadOnlySettings()
{
	//Program current version:
	curVersion = "3.2";

	//Program latest version source:
	updateUrl = "http://azconvert.sourceforge.net/lastver.txt";

	//Program home page:
	appHomepage = "http://azconvert.sourceforge.net/";
}

QString Settings::getUpdateUrl()
{
	return updateUrl;
}

QString Settings::getCurrentVersion()
{
	return curVersion;
}

QString Settings::getApplicationHomepage()
{
	return appHomepage;
}

Settings* Settings::GetInstance(QObject* parent)
{
    if (instance == NULL)
		instance = new Settings(parent);

    return instance;
}

bool Settings::GetWikiMode()
{
    return wikiMode;
}

void Settings::SetWikiMode(bool mode)
{
    wikiMode = mode;
	settings.setValue("wikimode", wikiMode);
}

bool Settings::getUpdateCheck()
{
	return updateCheck;
}

void Settings::setUpdateCheck(bool check)
{
	updateCheck = check;
	settings.setValue("updatecheck", updateCheck);
}

void Settings::LoadSettings()
{
	//Read each setting:
    wikiMode = settings.value("wikimode", false).toBool();
	updateCheck = settings.value("updatecheck", true).toBool();
}

/*void Settings::SaveSettings()
{
	//Save each setting:
    settings.setValue("wikimode", wikiMode);
	settings.setValue("updatecheck", updateCheck);
}*/
