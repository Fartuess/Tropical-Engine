#pragma once
#include "TransformComponent.h"
#include "Entity.h"
#include "Package.h"
#include <QtCore\qstring.h>

//using namespace glm;

class Level
{
public:
	QString name;
	Entity root;
	TransformComponent transform;	//is it needed since we can get same thing by using root?
private:
	Package internalPackage;
	QMap<QString, Package*> usedPackages;
public:
	Level(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, QString name = nullptr);
	//Level(glm::vec3 position, quat rotation, glm::vec3 scale, QString name = nullptr);
	Level(TransformComponent transform, QString name = nullptr);
	~Level(void);
};