#include "Component.h"
#include "Entity.h"

Component::Component(Entity* owner)
{
	if(owner != nullptr)
		this->setOwner(owner);
	else
		delete this;
}

Component::~Component(void)
{
	if(owner != nullptr)
	{
		owner->DetachComponent(this);
	}
}

Entity* Component::getOwner()
{
	return owner;
}

void Component::setOwner(Entity* owner)
{
	if(owner != nullptr)
	{
		if(this->owner != nullptr)
			this->owner->components.removeOne(this);
		this->owner = owner;
		this->owner->components.append(this);
	}
	else
	{
		Detach();
		delete this;
	}
}

void Component::Detach()
{
	owner->components.removeOne(this);
	this->owner = nullptr;
}