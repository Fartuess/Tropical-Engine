#pragma once

#include "Lighting_header.h"
#include "Scene_header.h"

class LightComponent: Component
{
public:
	Vec3 color;
	float brightness;

	LightComponent(Vec3 color, float brightness);
};