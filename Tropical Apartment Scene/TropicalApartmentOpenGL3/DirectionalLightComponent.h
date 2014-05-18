#pragma once

#include "Scene_header.h"
#include "Lighting_header.h"

class DirectionalLightComponent: LightComponent
{
public:
	Vec3 direction;
	bool isCastingShadow;

	DirectionalLightComponent(Vec3 direction, bool isCastingShadow = false);
	void UpdateShadow();
};