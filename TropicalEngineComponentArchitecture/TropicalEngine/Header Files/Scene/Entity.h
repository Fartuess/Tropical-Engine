#pragma once
#include <gtc/quaternion.hpp>

#include <QtCore/qlist.h>
#include <QtCore/qstring.h>

#include <Serialization/ISerializableToJSON.h>

#include "TransformComponent.h"

class Entity : public ISerializableToJSON
{
private:
	QList<Component*> components;	//Had to be on top to initialize before transform.

public:
	friend class Component;
	friend class PropertiesWidget;

	QList<Entity*> subobjects;

	TransformComponent transform;
	QString name;

	Entity(void);
	Entity(glm::vec3 position, glm::quat rotation, glm::vec3 scale);
	Entity(TransformComponent transform);
	~Entity(void);

	Entity* getParrent();
	void AttachSubobject(Entity* subobject);
	void AttachTo(Entity* parrent);
	void AttachComponent(Component* component);
	void DeleteComponent(Component* component);	//is needed?

	QString getTypeName() override;
	QJsonObject toJSON() override;

private:
	Entity* parrent;

	void DetachComponent(Component* component);
};