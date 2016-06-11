#include <Package/AssetManager.h>

namespace TropicalEngine
{
	AssetManager::AssetManager()
	{
		//TODO: Fix this temp solution.
		assetTypes = new QHash<QString, ISerializableJSON*>();
	}

	AssetManager::~AssetManager()
	{
	}

	void AssetManager::addAssetType(QString name, ISerializableJSON* typeHandle)
	{
		if (!assetTypes->contains(name))
		{
			(*assetTypes)[name] = typeHandle;
		}
	}

	ISerializableJSON* AssetManager::getTypeHandle(QString name)
	{
		return (*assetTypes)[name];
	}

	ISerializableJSON& AssetManager::createAsset(QJsonObject JSON)
	{
		return *(new Asset("", nullptr));
	}

}