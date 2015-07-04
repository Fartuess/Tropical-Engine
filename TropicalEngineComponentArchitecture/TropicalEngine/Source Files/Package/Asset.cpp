#include "Package/Asset.h"
#include "Package/AssetManager.h"

Asset Asset::templateObject = Asset::InitializeType();

Asset::Asset()
{
}


Asset::~Asset()
{
}

Asset Asset::InitializeType()
{
	Asset& asset = Asset();
	AssetManager::addAssetType("Asset", &asset);
	return asset;
}

QString Asset::GETTYPENAME("Asset");

QJsonObject Asset::toJSON()
{
	///TODO: implement this.
	QJsonObject JSON = QJsonObject();
	return JSON;
}

IDeserializableFromJSON& Asset::fromJSON(QJsonObject JSON)
{
	///TODO: implement this.
	return *(new Asset());
}