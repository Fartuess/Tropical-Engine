#pragma once
#include <gtc\quaternion.hpp>
#include <QtCore\qlist.h>
#include <QtCore\qstring.h>
#include "Scene\TransformComponent.h"
#include "Serialization/ISerializableToXML.h"
#include "Serialization/ISerializableToJSON.h"

class Entity : public ISerializableToXML, public ISerializableToJSON
{
private:
	friend class Component;
	friend class PropertiesWidget;

	Entity* parrent;
public:
	QList<Entity*> subobjects;
private:
	QList<Component*> components = QList<Component*>();

public:
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
private:
	void DetachComponent(Component* component);

public:
	QString toXML() override;
	QJsonObject toJSON() override;
};