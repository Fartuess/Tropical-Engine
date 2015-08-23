#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

#include <Package/Package.h>

#include "TransformComponent.h"
#include "Entity.h"

class Level : public ISerializableJSON
{
public:
	QString name;

	Level(glm::vec3 position, glm::quat rotation, glm::vec3 scale, QString name = nullptr);
	Level(TransformComponent transform, QString name = nullptr);
	~Level(void);

	Entity* const getRoot();
	Package* const getInternalPackage();
	//Package* const getInternalPackage();	//do we need that?

	void AttachObject(Entity* object);
	Level& operator<<(Entity* object);

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	Entity* root;

	Package* internalPackage;
	QMap<QString, Package*> usedPackages;

	Level(QString name);
};