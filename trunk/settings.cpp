#include <QSettings>
#include "settings.h"


Settings* Settings::instance = NULL;

Settings::Settings()
{
    LoadSettings();
}

Settings* Settings::GetInstance()
{
    if (instance == NULL)
        instance = new Settings();

    return instance;
}

bool Settings::GetWikiMode()
{
    return wikiMode;
}

void Settings::SetWikiMode(bool mode)
{
    wikiMode = mode;
    SaveSettings();
}

void Settings::LoadSettings()
{
    QSettings settings("AzTools", "AzConvert");
    wikiMode = settings.value("wikimode", false).toBool();
}

void Settings::SaveSettings()
{
    QSettings settings("AzTools", "AzConvert");
    settings.setValue("wikimode", wikiMode);
}
