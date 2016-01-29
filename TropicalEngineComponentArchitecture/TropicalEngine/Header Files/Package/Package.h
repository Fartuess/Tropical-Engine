#pragma once
#include <QtCore/qstring.h>
#include <QtCore/qpair.h>
#include <QtCore/qhash.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Package class used as containers for assets.
	  */
	#pragma endregion
	class Package : public ISerializableJSON
	{
	public:
		TYPENAME(Package)

		#pragma region documentation
		/**
		  * \brief Constructor for Package class.
		  *
		  * @param name Name for new Package.
		  */
		#pragma endregion
		Package(QString name);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~Package(void);

		#pragma region documentation
		/**
		  * \brief Initialized type in global typemap.
		  */
		#pragma endregion
		static Package InitializeType();

		#pragma region documentation
		/**
		  * \brief Gets name of the Package.
		  *
		  * @return Name of the Package.
		  */
		#pragma endregion
		QString getName();
		#pragma region documentation
		/**
		  * \brief Sets name of the Package.
		  *
		  * @param name Name to be set.
		  */
		#pragma endregion
		void setName(QString name);

		#pragma region documentation
		/**
		  * \brief Gets asset with name.
		  *
		  * @param name Name of asset to search.
		  * @return Found asset.
		  */
		#pragma endregion
		class Asset* const getAsset(QString name);
		#pragma region documentation
		/**
		  * \brief Adds asset to the package.
		  *
		  * @param asset Asset to be added.
		  */
		#pragma endregion
		void addAsset(class Asset* asset);
		#pragma region documentation
		/**
		  * \brief Adds asset to the package.
		  *
		  * @param asset Asset to be added.
		  */
		#pragma endregion
		Package& operator<<(class Asset* asset);

		#pragma region documentation
		/**
		  * \brief Serializes Package to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;

		#pragma region documentation
		/**
		  * \brief Deserializes Package from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Package object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	private:
		QHash<QString, class Asset*> assets;
		QString name;

		static Package templateObject;
	};

}