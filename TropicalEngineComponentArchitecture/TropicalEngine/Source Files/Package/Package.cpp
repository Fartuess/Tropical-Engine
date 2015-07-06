#include "Package/Package.h"
#include "Scene/Entity.h"
#include "Shader/Shader.h"
#include "Texture/Texture.h"
#include "Model/Model.h"

Package Package::templateObject = Package::InitializeType();

//QString Package::Asset::toXML()
//{
//	///TODO: implement it.
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
//		///TODO: send info to log
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
	Package& package = Package("TemplatePackage");
	AssetManager::addAssetType("Package", &package);
	return package;
}

QString Package::getName()
{
	return name;
}

void Package::setName(QString name)	//??
{
	this->name = name;
}

QString Package::GETTYPENAME("Package");

QString Package::toXML()
{
	QString XMLString = QString(getIndent() + "<Package name = \"" + name + "\">\n");
	increaseIndent();
	for (Asset asset : assets)
	{
		//XMLString += asset.toXML();
	}
	decreaseIndent();
	XMLString += QString(getIndent() + "</Package>\n");

	return XMLString;
}

QJsonObject Package::toJSON()
{
	return QJsonObject();
}

IDeserializableFromJSON& Package::fromJSON(QJsonObject JSON)
{
	///TODO: implement this.
	return *(new Package("TEMPORARY!"));
}