#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include <QNetworkAccessManager>


class MainWindow;


class Update : public QObject
{
	Q_OBJECT


public:
	static Update* getInstance(MainWindow* mainWindow, QObject* parent = NULL);
	~Update();
	void checkForUpdate();
	static bool compareVersions(const QString& curVersion, const QString& lastVersion);


private:
	Update(MainWindow* mainWindow, QObject* parent = NULL);


private slots:
	void replyGetLastVersionFinished(QNetworkReply*);


private:
	QNetworkAccessManager* networkManager;
	MainWindow* mainWindow;
	static Update* instance;
};

#endif // UPDATE_H
