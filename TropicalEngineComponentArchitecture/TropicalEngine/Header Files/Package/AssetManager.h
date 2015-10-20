#pragma once
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

#include "Asset.h"

/**
  * Class for managing asset data.
  */
class AssetManager
{
public:
	/**
	  * \brief Default constructor.
	  */
	AssetManager();

	/**
	  * \brief Default destructor.
	  */
	~AssetManager();

	/**
	  * \brief Adds type of assetable resources.
	  *
	  * @param name Name of type.
	  * @param typeHandle Instance of resource to be used as handle.  
	  */
	static void addAssetType(QString name, ISerializableJSON* typeHandle);

	/**
	  * \brief Gets handle to resource.
	  *
	  * @param name Name of the type.
	  * @return Handle object of wanted type.
	  */
	static ISerializableJSON* getTypeHandle(QString name);

	/**
	  * \brief Creates asset and resource from JSON.
	  *
	  * @param JSON JSON object for deserialization.
	  * @return Resource in created asset.
	  */
	static ISerializableJSON& createAsset(QJsonObject JSON);

private:
	static QHash<QString, ISerializableJSON*> assetTypes;
};

