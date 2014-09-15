#include "DirectionalLightComponent.h"

DirectionalLightComponent::DirectionalLightComponent(Entity* owner, glm::vec3 color, glm::vec3 direction, float brightness, bool isCastingShadows):LightComponent(owner, color, brightness, isCastingShadows)
{
	this->direction = direction;

	InitializeComponentType();
}

DirectionalLightComponent::~DirectionalLightComponent(void)
{
	///TODO: implement it.
}

void DirectionalLightComponent::InitializeComponentType()
{
	if(!isComponentTypeUsed(getName()))
	{
		SetParrentComponentType("Light Component");

		AddParameter("Direction", "Vec3");
	}
}

glm::vec3 DirectionalLightComponent::getDirection()
{
	return direction;
}

void DirectionalLightComponent::setDirection(glm::vec3 direction)
{
	this->direction = direction;
	if(castingShadows)
		DrawShadows();
}

void DirectionalLightComponent::Evaluate()
{
	///TODO: implement it.
}

void DirectionalLightComponent::DrawShadows()
{
	///TODO: implement it.
}

QString DirectionalLightComponent::COMPONENTGETNAME("DirectionalLight Component");

QString DirectionalLightComponent::toXML()
{
	///TODO: implement it.
	return QString(getIndent() + "<DirectionalLightComponent/>\n");
}