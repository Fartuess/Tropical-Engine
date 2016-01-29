#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Asset class is container for engine resources.
	  */
	#pragma endregion
	class Asset : public ISerializableJSON
	{
	public:
		TYPENAME(Asset)

		#pragma region documentation
		/**
		  * \brief Name of the asset.
		  */
		#pragma endregion
		QString name;

		#pragma region documentation
		/**
		  * \brief Name of type of this asset.
		  */
		#pragma endregion
		QString type;

		#pragma region documentation
		/**
		  * \brief Resource of this asset.
		  */
		#pragma endregion
		ISerializableJSON* asset;

		#pragma region documentation
		/**
		  * \brief Constructor of Asset.
		  *
		  * @param name Name of new Asset.
		  * @param asset Resource to be stored in Asset.
		  */
		#pragma endregion
		Asset(QString name, ISerializableJSON* asset);
		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~Asset();

		#pragma region documentation
		/**
		  * \brief Serializes Asset to JSON object.
		  *
		  * @return Result of serialization.
		  */
		#pragma endregion
		QJsonObject toJSON() override;
		#pragma region documentation
		/**
		  * \brief Deserializes Asset from JSON object.
		  *
		  * @param JSON JSON object to deserialize from.
		  * @return Asset object.
		  */
		#pragma endregion
		IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

	private:
		Asset();
	};

}