#include <Package/AssetManager.h>

QHash<QString, ISerializableJSON*> AssetManager::assetTypes;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::addAssetType(QString name, ISerializableJSON* typeHandle)
{
	if (!assetTypes.contains(name))
	{
		assetTypes[name] = typeHandle;
	}
}

ISerializableJSON* AssetManager::getTypeHandle(QString name)
{
	return assetTypes[name];
}

ISerializableJSON& AssetManager::createAsset(QJsonObject JSON)
{
	return *(new Asset("", nullptr));
}