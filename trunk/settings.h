#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QDate>
#include <QString>
#include <QSettings>


class Settings : public QObject
{
	//Q_OBJECT


public:
	static Settings* GetInstance(QObject* parent = NULL);
	//~Settings();
    void LoadSettings();
	//void SaveSettings();


private:
	Settings(QObject* parent = NULL);
	void initReadOnlySettings();


public:
    bool GetWikiMode();
	void SetWikiMode(bool);
	bool getUpdateCheck();
	void setUpdateCheck(bool);
	QString getUpdateUrl();
	QString getCurrentVersion();
	QString getApplicationHomepage();

private:
    bool wikiMode;
	bool updateCheck;
	QString curVersion;
	QString updateUrl;
	QString appHomepage;

private:
    static Settings* instance;
	QSettings settings;
};


#endif // SETTINGS_H
