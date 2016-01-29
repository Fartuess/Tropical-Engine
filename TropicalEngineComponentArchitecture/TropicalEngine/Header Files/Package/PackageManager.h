#pragma once
#include <QtCore/qpair.h>
#include <QtCore/qstring.h>
#include <QtCore/qhash.h>

#include "Package.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing packages.
	  */
	#pragma endregion
	class PackageManager
	{
	public:
		#pragma region documentation
		/**
		  * \brief Default constructor.
		  */
		#pragma endregion
		PackageManager(void);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~PackageManager(void);

		#pragma region documentation
		/**
		  * \brief Loads Package from file path.
		  *
		  * @param fileUrl path to Package file.
		  */
		#pragma endregion
		void LoadPackage(QString fileUrl);
		#pragma region documentation
		/**
		  * \brief Loads package from JSON.
		  *
		  * @param JSON JSON object for Package deserialization.
		  * @return Tells if Package is new.
		  */
		#pragma endregion
		bool LoadPackage(QJsonObject JSON);
		#pragma region documentation
		/**
		  * \brief Unloads the Package forcefully.
		  *
		  * @param name Name of the Package to unload.
		  */
		#pragma endregion
		void FlushPackage(QString name);

		#pragma region documentation
		/**
		  * \brief Checks if Package with given name is loaded.
		  *
		  * @param name Name of the Package to look for.
		  * @return is Package loaded.
		  */
		#pragma endregion
		bool isPackageLoaded(QString name);
		#pragma region documentation
		/**
		  * \brief Gets package with given name.
		  *
		  * @param name Name of the Package to look for.
		  * @return Found Package
		  */
		#pragma endregion
		Package* const getPackage(QString name);

	private:
		typedef QPair<Package*, int> PackageUsage;	//package and number of levels referencing to it

		QHash<QString, PackageUsage> packages;
	};

}