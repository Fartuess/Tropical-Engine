#pragma once
#include "Scene\TransformComponent.h"
#include "Scene/Entity.h"
#include "Package\Package.h"
#include <QtCore\qstring.h>
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

class Level : public ISerializableToXML, public ISerializableToJSON
{
public:
	QString name;
	Entity root;
	//TransformComponent transform;	//is it needed since we can get same thing by using root?
private:
	Package internalPackage;
	QMap<QString, Package*> usedPackages;
public:
	Level(glm::vec3 position, glm::quat rotation, glm::vec3 scale, QString name = nullptr);
	Level(TransformComponent transform, QString name = nullptr);
	~Level(void);

	QString toXML() override;
	QJsonObject toJSON() override;
};