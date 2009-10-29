#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    static Settings* GetInstance();
    Settings();
    void LoadSettings();
    void SaveSettings();

    //Setter and getter functions:
public:
    bool GetWikiMode();
    void SetWikiMode(bool mode);

private:
    bool wikiMode;

private:
    static Settings* instance;
};


#endif // SETTINGS_H
