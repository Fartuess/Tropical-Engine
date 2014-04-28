#pragma once

#include "Scene_header.h"

class GameObject;

class Component
{
public:
	GameObject* owner;

	Component(GameObject* owner);
};