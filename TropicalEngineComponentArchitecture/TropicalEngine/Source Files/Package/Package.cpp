#include "Package\Package.h"
#include "Scene/Entity.h"
#include "Shader\Shader.h"
#include "Texture\Texture.h"
#include "Model\Model.h"

Package::Asset::Asset(AssetType type, void* asset_ptr)
{
	this->type = type;
	this->asset_ptr = asset_ptr;
}

QString Package::Asset::toXML()
{
	///TODO: implement it.
	QString XMLString = "";
	switch(type)
	{
	case AssetType::Entity:
		XMLString += static_cast<Entity*>(asset_ptr)->toXML();
		break;
	case AssetType::Shader:
		XMLString += static_cast<Shader*>(asset_ptr)->toXML();
		break;
	case AssetType::Material:
		XMLString += static_cast<Material*>(asset_ptr)->toXML();
		break;
	case AssetType::Texture:
		XMLString += static_cast<Texture*>(asset_ptr)->toXML();
		break;
	case AssetType::Model:
		XMLString += static_cast<Model*>(asset_ptr)->toXML();
		break;
	default:
		///TODO: send info to log
		break;
	}
	
	return XMLString;
}

Package::Package(QString name)	//??
{
	this->name = name;
}

Package::~Package(void)	//??
{
}

QString Package::getName()
{
	return name;
}

void Package::setName(QString name)	//??
{
	this->name = name;
}

QString Package::toXML()
{
	QString XMLString = QString(getIndent() + "<Package name = \"" + name + "\">\n");
	increaseIndent();
	foreach(Asset asset, assets)
	{
		XMLString += asset.toXML();
	}
	decreaseIndent();
	XMLString += QString(getIndent() + "</Package>\n");

	return XMLString;
}