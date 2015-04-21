#include "Package/AssetManager.h"

QMap<QString, IDeserializableFromJSON*> AssetManager::assetTypes;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::addAssetType(QString name, IDeserializableFromJSON* typeHandle)
{
	if (!assetTypes.contains(name))
	{
		assetTypes[name] = typeHandle;
	}
}

IDeserializableFromJSON* AssetManager::getTypeHandle(QString name)
{
	return assetTypes[name];
}