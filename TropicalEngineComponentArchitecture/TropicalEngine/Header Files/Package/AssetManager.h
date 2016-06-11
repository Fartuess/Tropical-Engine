#pragma once
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

#include <Utills/Singleton.h>

#include "Asset.h"

namespace TropicalEngine
{

	#pragma region documentation
	/**
	  * \brief Class for managing Assets.
	  */
	#pragma endregion
	class AssetManager : public Singleton<AssetManager>
	{
	public:
		#pragma region documentation
				/**
				* \brief Default constructor.
				*/
		#pragma endregion
		AssetManager();

		#pragma region documentation
		/**
		  * \brief Default destructor.
		  */
		#pragma endregion
		~AssetManager();

		#pragma region documentation
		/**
		  * \brief Adds type of assetable resources.
		  *
		  * @param name Name of type.
		  * @param typeHandle Instance of resource to be used as handle.
		  */
		#pragma endregion
		void addAssetType(QString name, ISerializableJSON* typeHandle);
		#pragma region documentation
		/**
		  * \brief Gets handle to resource.
		  *
		  * @param name Name of the type.
		  * @return Handle object of wanted type.
		  */
		#pragma endregion
		ISerializableJSON* getTypeHandle(QString name);

		#pragma region documentation
		/**
		  * \brief Creates asset and resource from JSON.
		  *
		  * @param JSON JSON object for deserialization.
		  * @return Resource in created asset.
		  */
		#pragma endregion
		ISerializableJSON& createAsset(QJsonObject JSON);

	protected:
	

	private:
		//TODO: Should be shard through possible mutiple AssetManaagers.
		QHash<QString, ISerializableJSON*>* assetTypes;
	};

}