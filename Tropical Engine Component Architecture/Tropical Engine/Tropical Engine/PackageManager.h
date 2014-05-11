#pragma once
#include "singleton.h"
#include <QtCore\qpair.h>
#include <QtCore\qstring.h>
#include <QtCore\qmap.h>

class Package;

class PackageManager :
	public Singleton<PackageManager>
{
private:
	typedef QPair<Package*, int> PackageUsage;	//package and number of levels referencing to it

	QMap<QString, PackageUsage> packages;
public:
	PackageManager(void);
	~PackageManager(void);

	void LoadPackage(QString fileUrl);
	void FlushPackage(QString name);
};

