#pragma once
class Entity;

class Component
{
public:
	friend class Entity;
protected:
	Entity* owner;
public:
	Component(Entity* owner);
	~Component(void);
	Entity* getOwner();
	void setOwner(Entity* owner);
protected:
	void Detach();
};

