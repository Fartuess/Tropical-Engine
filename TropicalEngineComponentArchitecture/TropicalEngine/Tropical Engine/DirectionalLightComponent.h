#pragma once
#include "lightcomponent.h"

class DirectionalLightComponent :
	public LightComponent
{
private:
	glm::vec3 direction;
public:
	DirectionalLightComponent(Entity* owner, glm::vec3 color, glm::vec3 direction, float brightness = 1.0f, bool isCastingShadows = false);
	~DirectionalLightComponent(void);

	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);

	void Evaluate();
	void DrawShadows();

	QString toXML() override;
};

