#pragma once
#include <gtc/quaternion.hpp>

#include <QtCore/qlist.h>
#include <QtCore/qstring.h>

#include <Serialization/ISerializableJSON.h>

#include "TransformComponent.h"

/**
  * Basic scene object with transform node. Functionality is extended by attaching components.
  */
class Entity : public ISerializableJSON
{
private:
	QList<Component*> components;	//Had to be on top to initialize before transform.

public:
	TYPENAME("Entity")

	friend class Component;
	friend class PropertiesWidget;

	TransformComponent transform;
	QString name;

	Entity(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)), glm::vec3 scale = glm::vec3(1.0f));
	Entity(TransformComponent transform);
	~Entity(void);

	Entity* getParrent();
	void AttachSubobject(Entity* subobject);
	void AttachTo(Entity* parrent);
	Entity& operator<<(Entity* child);
	const QList<Entity*>& getSubobjects();

	void AttachComponent(Component* component);
	void DeleteComponent(Component* component);	//is needed?
	Entity& operator<<(Component* component);

	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

private:
	Entity* parrent;

	QList<Entity*> subobjects;

	void DetachComponent(Component* component);
};