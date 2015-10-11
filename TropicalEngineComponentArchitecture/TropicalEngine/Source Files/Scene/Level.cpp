#include <TropicalEngineApplication.h>
#include <Package/PackageManager.h>

#include <Scene/Level.h>

Level::Level(QString name, glm::vec3 position, glm::quat rotation, glm::vec3 scale) : root(new Entity()), internalPackage(new Package(name))
{
	///TODO: implement it.
}

Level::Level(TransformComponent transform, QString name) : root(new Entity()), internalPackage(new Package(name))
{
	///TODO: implement it.
}

Level::~Level(void)
{
	delete root;
	delete internalPackage;
	///TODO: figure out unloading used packages if neccessary.
}

Entity* const Level::getRoot()
{
	return root;
}

Package* const Level::getInternalPackage()
{
	return internalPackage;
}

void Level::AttachObject(Entity* object)
{
	root->AttachSubobject(object);
}

Level& Level::operator<<(Entity* object)
{
	AttachObject(object);
	return *this;
}

QString Level::GETTYPENAME("Level");

//QString Level::toXML()
//{
//	///TODO: finish implementing it.
//	QString XMLString = QString(getIndent() + "<Level name = \"" + name + "\">\n");
//	increaseIndent();
//	XMLString += internalPackage.toXML();
//	///TODO: Saved used packages to separated files.
//	/*
//	foreach(Package* package, usedPackages)
//	{
//		XMLString += package->toXML();
//	}*/
//	//XMLString += root.toXML();
//	decreaseIndent();
//	XMLString += QString(getIndent() + "</Level>\n");
//
//	return XMLString;
//}

QJsonObject Level::toJSON()
{
	QJsonObject JSON = QJsonObject();
	JSON["name"] = name;
	JSON["url"] = "PLACEHOLDER";
	QJsonObject rootObject = root->toJSON();
	JSON["root entity"] = rootObject;

	JSON["internal package"] = internalPackage->toJSON();

	QJsonArray usedPackagesJSON;
	for (Package* package : usedPackages)
	{
		usedPackagesJSON.append("PLACEHOLDER FOR USED PACKAGE URL");
	}
	JSON["used packages"] = usedPackagesJSON;

	return JSON;
}

IDeserializableFromJSON* Level::fromJSON(QJsonObject JSON)
{
	Level* object = new Level(JSON["name"].toString());
	object->root = static_cast<Entity*>(AssetManager::getTypeHandle("Asset")->fromJSON(JSON["root entity"].toObject()));

	object->internalPackage = static_cast<Package*>(AssetManager::getTypeHandle("Package")->fromJSON(JSON["internal Package"].toObject()));

	for (QJsonValueRef usedPackageRef : JSON["used packages"].toArray())
	{
		TropicalEngineApplication::instance()->packageManager->LoadPackage(usedPackageRef.toObject());
		QString packageName = usedPackageRef.toObject()["name"].toString();
		usedPackages[packageName] = TropicalEngineApplication::instance()->packageManager->getPackage(packageName);
	}

	return object;
}