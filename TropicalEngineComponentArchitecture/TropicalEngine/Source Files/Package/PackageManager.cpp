#include <QtCore/qjsonobject.h>

#include <Package/PackageManager.h>
#include <Package/AssetManager.h>

namespace TropicalEngine
{

	PackageManager::PackageManager(void)
	{
	}

	PackageManager::~PackageManager(void)
	{
		// TODO: implement it.
	}

	void PackageManager::LoadPackage(QString fileUrl)
	{
		// TODO: implement it.
	}

	bool PackageManager::LoadPackage(QJsonObject JSON)
	{
		// TODO: implement it.
		bool isNewPackage = false;
		QString usedPackageName = JSON["name"].toString();
		if (isPackageLoaded(usedPackageName))
		{
			packages[usedPackageName].second++;
			isNewPackage = false;
		}
		else
		{
			packages[usedPackageName] = PackageUsage(static_cast<Package*>(AssetManager::getTypeHandle("Package")->fromJSON(JSON)), 1);
			isNewPackage = true;
		}
		return isNewPackage;
	}

	void PackageManager::FlushPackage(QString name)
	{
		// TODO: implement it.
	}

	bool PackageManager::isPackageLoaded(QString name)
	{
		return packages.contains(name);
	}

	Package* const PackageManager::getPackage(QString name)
	{
		return packages[name].first;
	}

}