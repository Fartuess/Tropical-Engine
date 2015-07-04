#include "Scene\Level.h"

Level::Level(glm::vec3 position, glm::quat rotation, glm::vec3 scale, QString name): internalPackage(name)
{
	///TODO: implement it.
}

Level::Level(TransformComponent transform, QString name): internalPackage(name)
{
	///TODO: implement it.
}

Level::~Level(void)
{
	///TODO: figure out unloading used packages if neccessary.
}

QString Level::GETTYPENAME("Level");

QString Level::toXML()
{
	///TODO: finish implementing it.
	QString XMLString = QString(getIndent() + "<Level name = \"" + name + "\">\n");
	increaseIndent();
	XMLString += internalPackage.toXML();
	///TODO: Saved used packages to separated files.
	/*
	foreach(Package* package, usedPackages)
	{
		XMLString += package->toXML();
	}*/
	//XMLString += root.toXML();
	decreaseIndent();
	XMLString += QString(getIndent() + "</Level>\n");

	return XMLString;
}

QJsonObject Level::toJSON()
{
	QJsonObject JSON = QJsonObject();
	JSON["name"] = name;
	JSON["url"] = "PLACEHOLDER";
	QJsonObject rootObject = root.toJSON();
	JSON["root entity"] = rootObject;

	///TODO: Packages serialization.

	return JSON;
}