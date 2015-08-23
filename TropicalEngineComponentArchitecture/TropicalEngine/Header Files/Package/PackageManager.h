#pragma once
#include <QtCore/qpair.h>
#include <QtCore/qstring.h>
#include <QtCore/qmap.h>


class PackageManager
{
public:
	PackageManager(void);
	~PackageManager(void);

	void LoadPackage(QString fileUrl);
	bool LoadPackage(QJsonObject JSON);
	void FlushPackage(QString name);

	bool isPackageLoaded(QString name);
	class Package* const getPackage(QString name);

private:
	typedef QPair<class Package*, int> PackageUsage;	//package and number of levels referencing to it

	QMap<QString, PackageUsage> packages;
};

