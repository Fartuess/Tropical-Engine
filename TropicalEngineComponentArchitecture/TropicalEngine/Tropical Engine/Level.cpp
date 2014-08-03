#include "Level.h"

Level::Level(glm::vec3 position, glm::quat rotation, glm::vec3 scale, QString name):transform(&(this->root)), internalPackage(name)
{
	///TODO: implement it.
}

Level::Level(TransformComponent transform, QString name):transform(&(this->root)), internalPackage(name)
{
	///TODO: implement it.
}

Level::~Level(void)
{
	///TODO: implement it.
}

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
	XMLString += root.toXML();
	decreaseIndent();
	XMLString += QString(getIndent() + "</Level>\n");

	return XMLString;
}