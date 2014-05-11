#include "LightComponent.h"
#include "LightManager.h"


LightComponent::LightComponent(Entity* owner, glm::vec3 color, float brightness, bool isCastingShadows):Component(owner)
{
	this->color = color;
	this->brightness = brightness;
	this->castingShadows = isCastingShadows;
	LightManager::Instance().lights.append(this);
	Evaluate();
	if(castingShadows)
		DrawShadows();
}


LightComponent::~LightComponent(void)
{
	LightManager::Instance().lights.removeOne(this);
}

bool LightComponent::isCastingShadows()
{
	return castingShadows;
}

void LightComponent::isCastingShadows(bool isCastingShadows)
{
	castingShadows = true;
	DrawShadows();
}

void LightComponent::Evaluate()
{
	///TODO: implement it.
}

void LightComponent::DrawShadows()
{
	///TODO: implement it.
}
