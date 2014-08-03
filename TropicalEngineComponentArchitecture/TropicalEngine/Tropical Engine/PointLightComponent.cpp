#include "PointLightComponent.h"

PointLightComponent::PointLightComponent(Entity* owner, glm::vec3 color, float brightness, float radius, float attenuation, bool isCastingShadows) :
	LightComponent(owner, color, brightness, isCastingShadows)
{
	this->radius = radius;
	this->attenuation = attenuation;
}

PointLightComponent::~PointLightComponent(void)
{
	///TODO: implement it.
}

float PointLightComponent::getRadius()
{
	return radius;
}

void PointLightComponent::setRadius(float radius)
{
	this->radius = radius;
	Evaluate();
	if(castingShadows)
		DrawShadows();
}

void PointLightComponent::Evaluate()
{
	///TODO: implement it.
}

void PointLightComponent::DrawShadows()
{
	///TODO: implement it.
}

QString PointLightComponent::toXML()
{
	///TODO: implement it.
	return QString(getIndent() + "<PointLightComponent/>\n");
}