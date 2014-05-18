#pragma once

#include "Utility_header.h"
#include "Component.h"

class GameObject;
//class Component;

class RenderComponent: public Component
{
public:

	RenderComponent(GameObject* owner);
	void Draw(Vec3* position, Vec3* rotation, Vec3* scale, GLUSfloat time, GLUSfloat scaleMatrix[16]);
};