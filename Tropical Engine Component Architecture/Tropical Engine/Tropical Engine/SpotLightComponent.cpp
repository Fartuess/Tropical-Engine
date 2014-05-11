#include "SpotLightComponent.h"


SpotLightComponent::SpotLightComponent(Entity* owner, glm::vec3 color, float brightness, float radius, float attenuation,
									   float outerConeRadius, float innerConeRadius, bool isCastingShadows) :
LightComponent(owner, color, brightness, isCastingShadows)
{
	this->radius = radius;
	this->attenuation = attenuation;
	this->outerConeRadius = outerConeRadius;
	this->innerConeRadius = innerConeRadius;
}


SpotLightComponent::~SpotLightComponent(void)
{
}

float SpotLightComponent::getRadius()
{
	return radius;
}

void SpotLightComponent::setRadius(float radius)
{
	this->radius = radius;
	Evaluate();
	if(castingShadows)
		DrawShadows();
}

float SpotLightComponent::getOuterConeRadius()
{
	return outerConeRadius;
}

void SpotLightComponent::setOuterConeRadius(float outerConeRadius)
{
	this->outerConeRadius = outerConeRadius;
	Evaluate();
	if(castingShadows)
		DrawShadows();
}

void SpotLightComponent::Evaluate()
{
	///TODO: implement it.
}

void SpotLightComponent::DrawShadows()
{
	///TODO: implement it.
}
