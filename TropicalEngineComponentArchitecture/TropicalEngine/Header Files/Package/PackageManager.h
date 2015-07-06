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
	void FlushPackage(QString name);

private:
	typedef QPair<class Package*, int> PackageUsage;	//package and number of levels referencing to it

	QMap<QString, PackageUsage> packages;
};

