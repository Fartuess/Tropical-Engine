#include "LightComponent.h"
#include "LightController.h"

#include "TropicalEngineApplication.h"


LightComponent::LightComponent(Entity* owner, glm::vec3 color, float brightness, bool isCastingShadows):Component(owner)
{
	this->color = color;
	this->brightness = brightness;
	this->castingShadows = isCastingShadows;
	TropicalEngineApplication::instance()->lightController->lights.append(this);
	Evaluate();
	if(castingShadows)
		DrawShadows();
}


LightComponent::~LightComponent(void)
{
	TropicalEngineApplication::instance()->lightController->lights.removeOne(this);
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
