#include "Light/DirectionalLightComponent.h"

DirectionalLightComponent DirectionalLightComponent::templateObject = DirectionalLightComponent::InitializeType();

DirectionalLightComponent::DirectionalLightComponent() {}

DirectionalLightComponent::DirectionalLightComponent(Entity* owner, glm::vec3 color, glm::vec3 direction, float brightness, bool isCastingShadows):LightComponent(owner, color, brightness, isCastingShadows)
{
	this->direction = direction;

	InitializeComponentType();
}

DirectionalLightComponent::~DirectionalLightComponent(void)
{
	///TODO: implement it.
}

DirectionalLightComponent DirectionalLightComponent::InitializeType()
{
	DirectionalLightComponent& directionalLightComponent = *(new DirectionalLightComponent());
	AssetManager::addAssetType("Directional Light Component", &directionalLightComponent);
	return directionalLightComponent;
}

void DirectionalLightComponent::InitializeComponentType()
{
	if (!isComponentTypeUsed(getTypeName()))
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
	if (castingShadows)
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

QString DirectionalLightComponent::GETTYPENAME("DirectionalLight Component");

//QString DirectionalLightComponent::toXML()
//{
//	///TODO: implement it.
//	return QString(getIndent() + "<DirectionalLightComponent/>\n");
//}

QJsonObject DirectionalLightComponent::toJSON()
{
	///TODO: implement it.
	QJsonObject JSON = LightComponent::toJSON();
	QJsonObject directionObject = QJsonObject();
	directionObject["x"] = direction.x;
	directionObject["y"] = direction.y;
	directionObject["z"] = direction.z;
	JSON["direction"] = directionObject;

	return JSON;
}

IDeserializableFromJSON& DirectionalLightComponent::fromJSON(QJsonObject JSON)
{
	///TODO: implement this.
	return *(new DirectionalLightComponent());
}