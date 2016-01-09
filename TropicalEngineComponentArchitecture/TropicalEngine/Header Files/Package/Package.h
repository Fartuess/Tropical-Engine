#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qpair.h>
#include <QtCore/qmap.h>

#include <Serialization/ISerializableJSON.h>

#include "Asset.h"

namespace TropicalEngine
{

	/**
	  * Package class used as containers for assets.
	  */
	class Package : public ISerializableJSON
	{
	public:
		TYPENAME(Package)

		/**
		  * \brief Constructor for Package class.
		  *
		  * @param name Name for new Package.
		  */
		Package(QString name);

		/**
		  * \brief Default destructor.
		  */
		~Package(void);

		/**
		  * \brief Initialized type in global typemap.
		  */
		static Package InitializeType();

		/**
		  * \brief Gets name of the Package.
		  *
		  * @return Name of the Package.
		  */
		QString getName();

		/**
		  * \brief Sets name of the Package.
		  *
		  * @param name Name to be set.
		  */
		void setName(QString name);

		/**
		  * \brief Gets asset with name.
		  *
		  * @param name Name of asset to search.
		  * @return Found asset.
		  */
		Asset* const getAsset(QString name);

		/**
		  * \brief Adds asset to the package.
		  *
		  * @param asset Asset to be added.
		  */
		void addAsset(Asset* asset);

		/**
		  * \brief Adds asset to the package.
		  *
		  * @param asset Asset to be added.
		  */
		Package& operator<<(Asset* asset);

		/**
		  * \brief Serializes Package to JSON object.
		  *
		  * @return Result of serialization.
		  */
		QJsonObject toJSON() override;

		/**
		  * \brief Deserializes Package from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Package object.
		  */
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	private:
		QMap<QString, Asset*> assets;
		QString name;

		static Package templateObject;
	};

}