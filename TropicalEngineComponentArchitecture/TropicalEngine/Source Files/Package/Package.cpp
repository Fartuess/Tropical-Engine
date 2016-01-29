#include <Package/Package.h>
#include <Scene/Entity.h>
#include <Shader/Shader.h>
#include <Texture/Texture.h>
#include <Model/Model.h>

namespace TropicalEngine
{

	Package Package::templateObject = Package::InitializeType();

	//QString Package::Asset::toXML()
	//{
	//	// TODO: implement it.
	//	QString XMLString = "";
	//	switch (type)
	//	{
	//	case AssetType::Entity:
	//		XMLString += static_cast<Entity*>(asset_ptr)->toXML();
	//		break;
	//	case AssetType::Shader:
	//		XMLString += static_cast<Shader*>(asset_ptr)->toXML();
	//		break;
	//	case AssetType::Material:
	//		XMLString += static_cast<Material*>(asset_ptr)->toXML();
	//		break;
	//	case AssetType::Texture:
	//		XMLString += static_cast<Texture*>(asset_ptr)->toXML();
	//		break;
	//	case AssetType::Model:
	//		XMLString += static_cast<Model*>(asset_ptr)->toXML();
	//		break;
	//	default:
	//		// TODO: send info to log
	//		break;
	//	}
	//	
	//	return XMLString;
	//}

	Package::Package(QString name)	//??
	{
		this->name = name;
	}

	Package::~Package(void)	//??
	{
	}

	Package Package::InitializeType()
	{
		// TODO: Figure out what to do with this.
		Package* package = new Package("TemplatePackage");
		//AssetManager::addAssetType("Package", package);
		return *package;
	}

	QString Package::getName()
	{
		return name;
	}

	void Package::setName(QString name)	//??
	{
		this->name = name;
	}

	Asset* const Package::getAsset(QString name)
	{
		return assets[name];
	}

	void Package::addAsset(Asset* asset)
	{
		assets[asset->name] = asset;
	}

	Package& Package::operator<<(Asset* asset)
	{
		addAsset(asset);
		return *this;
	}


	//QString Package::toXML()
	//{
	//	QString XMLString = QString(getIndent() + "<Package name = \"" + name + "\">\n");
	//	increaseIndent();
	//	for (Asset asset : assets)
	//	{
	//		//XMLString += asset.toXML();
	//	}
	//	decreaseIndent();
	//	XMLString += QString(getIndent() + "</Package>\n");
	//
	//	return XMLString;
	//}

	QJsonObject Package::toJSON()
	{
		QJsonObject JSON;
		JSON["name"] = name;
		QJsonArray assetArray;

		for (Asset* asset : assets)
		{
			assetArray.push_back(asset->toJSON());
		}

		JSON["assets"] = assetArray;

		return JSON;
	}

	IDeserializableFromJSON* Package::fromJSON(QJsonObject JSON)
	{
		Package* package = new Package(JSON["name"].toString());

		for (QJsonValueRef assetRef : JSON["assets"].toArray())
		{
			QJsonObject assetJSON = assetRef.toObject();

			Asset* asset = static_cast<Asset*>(AssetManager::getTypeHandle("Asset")->fromJSON(assetJSON));

			package->assets[assetJSON["name"].toString()] = asset;
		}

		return package;
	}

}