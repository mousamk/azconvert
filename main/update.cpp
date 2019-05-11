#include <QNetworkReply>
#include <QDebug>

#include "update.h"
#include "util.h"
#include "settings.h"
#include "config.h"


//Allocate memory for static member variable:
Update* Update::instance = NULL;


Update* Update::getInstance(QObject *parent)
{
	if (NULL == instance)
        instance = new Update(parent);

	return instance;
}


Update::Update(QObject* parent)
	: QObject(parent)
{
	//Initialize:
	networkManager = new QNetworkAccessManager(parent);

	//Setup connections:
	connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyGetLastVersionFinished(QNetworkReply*)));
}

Update::~Update()
{
	//Free network manager object:
	DELETE_AND_NULL(networkManager);
}

void Update::replyGetLastVersionFinished(QNetworkReply* reply)
{
	//Check if successful:
	if (reply->error() == QNetworkReply::NoError)
	{
		//Read downloaded data:
		QByteArray data = reply->readAll();
		QString ver(data);

		//If it's a new release, Notify main window:
        if (compareVersions(APP_VERSION, ver))
            emit newVersionAvailable(ver);
		else
			qDebug() << "We're using the latest version!";
	}
	else
	{
		//Ignore!
		qDebug() << "Error in getting last version page: " << reply->errorString();
	}
}


void Update::checkForUpdate()
{
	//Issue request:
    networkManager->get(QNetworkRequest(QUrl(APP_UPDATE_URL)));
}


bool Update::compareVersions(const QString &curVersion, const QString &lastVersion)
{
	QString p1, p2;
	int ind1, ind2;
	int end1, end2;
	int n1, n2;
	bool ok1, ok2;

	//Compare first (major) numbers:
	end1 = curVersion.indexOf(".");
	end2 = curVersion.indexOf(".");

	if (-1 == end1 || -1 == end2)
		return false;

	p1 = curVersion.left(end1);
	p2 = lastVersion.left(end2);

	n1 = p1.toInt(&ok1);
	n2 = p2.toInt(&ok2);

	if (!ok1 || !ok2)
		return false;

	if (n2 > n1)	//It's a major new release!
		return true;

	//Compare second (minor) numbers:
	ind1 = end1+1;
	ind2 = end2+1;
	end1 = curVersion.indexOf(".", ind1);
	end2 = lastVersion.indexOf(".", ind2);

	if (-1 == end1 || -1 == end2)
		return false;

	p1 = curVersion.mid(ind1, end1-ind1);
	p2 = lastVersion.mid(ind2, end2-ind2);

	n1 = p1.toInt(&ok1);
	n2 = p2.toInt(&ok2);

	if (!ok1 || !ok2)
		return false;

	if (n2 > n1)	//It's a minor new release!
		return true;


	//Not checking the third and fourth numbers,
    // cause they aren't worth informing user!
	return false;
}
