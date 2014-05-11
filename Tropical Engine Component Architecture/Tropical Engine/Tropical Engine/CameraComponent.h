#pragma once
#include "component.h"
class CameraComponent :
	public Component
{
public:
	CameraComponent(Entity* owner);
	~CameraComponent(void);
};

