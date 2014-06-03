#pragma once
#include "_Math.h"
#include "component.h"

//Should it be an abstract class?
class LightComponent :
	public Component
{
public:
	glm::vec3 color;
	float brightness;
protected:
	bool castingShadows;
public:
	LightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, bool isCastingShadows = false);
	~LightComponent(void);

	bool isCastingShadows();
	void isCastingShadows(bool isCastingShadows);

	void Evaluate();
	void DrawShadows();
};