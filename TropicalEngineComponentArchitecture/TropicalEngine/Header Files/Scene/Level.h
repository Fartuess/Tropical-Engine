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

	Level(QString name, glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3 scale = glm::vec3(1.0f));
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
	QHash<QString, Package*> usedPackages;
};