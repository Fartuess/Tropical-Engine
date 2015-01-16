#include "Light\PointLightComponent.h"

PointLightComponent::PointLightComponent(Entity* owner, glm::vec3 color, float brightness, float radius, float attenuation, bool isCastingShadows) :
	LightComponent(owner, color, brightness, isCastingShadows)
{
	this->radius = radius;
	this->attenuation = attenuation;

	InitializeComponentType();
}

PointLightComponent::~PointLightComponent(void)
{
	///TODO: implement it.
}

void PointLightComponent::InitializeComponentType()
{
	if(!isComponentTypeUsed(getName()))
	{
		SetParrentComponentType("Light Component");

		AddParameter("Radius", "Float");
		AddParameter("Attenuation", "Float");
	}
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

QString PointLightComponent::COMPONENTGETNAME("PointLight Component");

QString PointLightComponent::toXML()
{
	///TODO: implement it.
	return QString(getIndent() + "<PointLightComponent/>\n");
}

QJsonObject PointLightComponent::toJSON()
{
	///TODO: implement it.
	QJsonObject JSON = LightComponent::toJSON();
	JSON["radius"] = radius;
	JSON["attenuation"] = attenuation;

	return JSON;
}