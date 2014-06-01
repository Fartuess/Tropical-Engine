#pragma once
#include <QtCore\qlist.h>
#include <QtCore\qstring.h>
#include "_Math.h"
#include "TransformComponent.h"

class Entity
{
private:
	friend class Component;

	Entity* parrent;
public:
	QList<Entity*> subobjects;
private:
	QList<Component*> components;

public:
	TransformComponent transform;
	QString* name;

	Entity(void);
	Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	//Entity(glm::vec3 position, quat rotation, glm::vec3 scale);
	Entity(TransformComponent transform);
	~Entity(void);

	Entity* getParrent();
	void AttachSubobject(Entity* subobject);
	void AttachTo(Entity* parrent);
	void AttachComponent(Component* component);
	void DeleteComponent(Component* component);	//is needed?
private:
	void DetachComponent(Component* component);
};