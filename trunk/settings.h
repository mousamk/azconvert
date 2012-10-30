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


public:
    bool getWikiMode() const;
    void setWikiMode(bool);
    bool getUpdateCheck() const;
	void setUpdateCheck(bool);
    QString getLanguage() const;
    void setLanguage(QString lang);


private:
    bool wikiMode;
	bool updateCheck;
    QString language;


private:
    static Settings* instance;
	QSettings settings;
};


#endif // SETTINGS_H
