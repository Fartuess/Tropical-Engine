#pragma once
#include "TransformComponent.h"
#include "Entity.h"
#include "Package.h"
#include <QtCore\qstring.h>
#include "ISerializableToXML.h"

class Level : public ISerializableToXML
{
public:
	QString name;
	Entity root;
	TransformComponent transform;	//is it needed since we can get same thing by using root?
private:
	Package internalPackage;
	QMap<QString, Package*> usedPackages;
public:
	Level(glm::vec3 position, glm::quat rotation, glm::vec3 scale, QString name = nullptr);
	Level(TransformComponent transform, QString name = nullptr);
	~Level(void);

	QString toXML() override;
};