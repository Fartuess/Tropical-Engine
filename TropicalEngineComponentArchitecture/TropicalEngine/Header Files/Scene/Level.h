#pragma once
#include <QtCore/qstring.h>

#include <Serialization/ISerializableToJSON.h>

#include <Package/Package.h>

#include "TransformComponent.h"
#include "Entity.h"

class Level : public ISerializableToJSON
{
public:
	QString name;
	Entity root;

	Level(glm::vec3 position, glm::quat rotation, glm::vec3 scale, QString name = nullptr);
	Level(TransformComponent transform, QString name = nullptr);
	~Level(void);

	QString getTypeName() override;
	QJsonObject toJSON() override;

private:
	Package internalPackage;
	QMap<QString, Package*> usedPackages;
};