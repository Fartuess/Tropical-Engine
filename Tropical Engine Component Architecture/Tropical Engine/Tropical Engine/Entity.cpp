#include "Entity.h"


Entity::Entity(void):transform(this)
{
	///TODO: implement it.
}

Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):transform(this, position, rotation, scale)
{
	///TODO: implement it.
}

/*
Entity::Entity(glm::vec3 position, quat rotation, glm::vec3 scale):transform(this, position, rotation, scale)
{

}
*/

Entity::Entity(TransformComponent transform):transform(transform)
{
	///TODO: implement it.
}

Entity::~Entity(void)
{
	///TODO: implement it.
}

Entity* Entity::getParrent()
{
	return parrent;
}

void Entity::AttachSubobject(Entity* subobject)
{
	if(subobject != nullptr)
	{
		subobjects.append(subobject);
		subobject->parrent = this;
	}
}

void Entity::AttachTo(Entity* parrent)
{
	if(parrent != nullptr)
	{
		this->parrent = parrent;
		parrent->subobjects.append(this);
	}
}

void Entity::AttachComponent(Component* component)
{
	if(component != nullptr)
	{
		component->getOwner()->DetachComponent(component);
		component->owner = this;
		components.append(component);
	}
}

void Entity::DeleteComponent(Component* component)
{
	if(component != nullptr)
	{
		components.removeOne(component);
		delete component;
	}
}

void Entity::DetachComponent(Component* component)
{
	if(component != nullptr)
	{
		components.removeOne(component);
		component->owner = nullptr;
	}
}