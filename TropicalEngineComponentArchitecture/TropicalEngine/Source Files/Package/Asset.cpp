#include <Package/Asset.h>
#include <Package/AssetManager.h>

namespace TropicalEngine
{

	//Asset Asset::templateObject = Asset::InitializeType();

	Asset::Asset(QString name, ISerializableJSON* asset)
	{
		this->name = name;
		this->type = asset->getTypeName();
		this->asset = asset;
	}

	//Asset::Asset(QString name, QString type, QJsonObject JSON)
	//{
	//}

	Asset::~Asset()
	{
	}

	//Asset Asset::InitializeType()
	//{
	//	Asset& asset = Asset();
	//	AssetManager::addAssetType("Asset", &asset);
	//	return asset;
	//}

	QJsonObject Asset::toJSON()
	{
		// TODO: Make cheating unnecessary.
		QJsonObject JSON = QJsonObject();
		JSON["name"] = name;
		JSON["typename"] = asset->getTypeName();
		JSON["asset"] = asset->toJSON();
		return JSON;
	}

	IDeserializableFromJSON* Asset::fromJSON(QJsonObject JSON)
	{
		Asset* asset = new Asset();
		asset->name = JSON["name"].toString();
		asset->type = JSON["typeName"].toString();
		//Assuming that all Assets can be serialized back again.
		asset->asset = static_cast<ISerializableJSON*>(AssetManager::instance().getTypeHandle(asset->type)->fromJSON(JSON["asset"].toObject()));

		return asset;
	}

	Asset::Asset()
	{

	}

}