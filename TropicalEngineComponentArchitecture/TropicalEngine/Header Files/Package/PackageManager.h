#pragma once
#include <QtCore/qpair.h>
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

/**
  * Class for managing packages.
  */
class PackageManager
{
public:
	/**
	  * \brief Default constructor.
	  */
	PackageManager(void);
	/**
	  * \brief Default destructor.
	  */
	~PackageManager(void);

	/**
	  * \brief Loads Package from file path.
	  *
	  * @param fileUrl path to Package file.
	  */
	void LoadPackage(QString fileUrl);

	/**
	  * \brief Loads package from JSON.
	  *
	  * @param JSON JSON object for Package deserialization.
	  * @return Tells if Package is new.
	  */
	bool LoadPackage(QJsonObject JSON);

	/**
	  * \brief Unloads the Package forcefully.
	  *
	  * @param name Name of the Package to unload.
	  */
	void FlushPackage(QString name);

	/**
	  * \brief Checks if Package with given name is loaded.
	  *
	  * @param name Name of the Package to look for.
	  * @return is Package loaded.
	  */
	bool isPackageLoaded(QString name);

	/**
	  * \brief Gets package with given name.
	  *
	  * @param name Name of the Package to look for.
	  * @return Found Package
	  */
	class Package* const getPackage(QString name);

private:
	typedef QPair<class Package*, int> PackageUsage;	//package and number of levels referencing to it

	QHash<QString, PackageUsage> packages;
};

