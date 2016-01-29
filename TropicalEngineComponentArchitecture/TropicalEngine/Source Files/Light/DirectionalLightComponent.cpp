#include <Light/DirectionalLightComponent.h>

namespace TropicalEngine
{

	DirectionalLightComponent DirectionalLightComponent::templateObject = DirectionalLightComponent::InitializeType();

	DirectionalLightComponent::DirectionalLightComponent() {}

	DirectionalLightComponent::DirectionalLightComponent(Entity* owner, glm::vec3 color, glm::vec3 direction, float brightness, bool isCastingShadows) :LightComponent(owner, color, brightness, isCastingShadows)
	{
		this->direction = direction;

		InitializeComponentType();
	}

	DirectionalLightComponent::~DirectionalLightComponent(void)
	{
		// TODO: implement it.
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
		// TODO: implement it.
	}

	void DirectionalLightComponent::DrawShadows()
	{
		// TODO: implement it.
	}

	//QString DirectionalLightComponent::toXML()
	//{
	//	// TODO: implement it.
	//	return QString(getIndent() + "<DirectionalLightComponent/>\n");
	//}

	QJsonObject DirectionalLightComponent::toJSON()
	{
		QJsonObject JSON = LightComponent::toJSON();
		QJsonObject directionObject = QJsonObject();
		directionObject["x"] = direction.x;
		directionObject["y"] = direction.y;
		directionObject["z"] = direction.z;
		JSON["direction"] = directionObject;

		return JSON;
	}

	IDeserializableFromJSON* DirectionalLightComponent::fromJSON(QJsonObject JSON)
	{
		DirectionalLightComponent* object = new DirectionalLightComponent();

		QJsonObject colorJSON = JSON["color"].toObject();
		object->color = glm::vec3(colorJSON["r"].toDouble(), colorJSON["g"].toDouble(), colorJSON["b"].toDouble());
		object->brightness = JSON["brightness"].toDouble();
		object->castingShadows = JSON["casting shadows"].toBool();

		QJsonObject directionJSON = JSON["direction"].toObject();
		object->direction = glm::vec3(directionJSON["x"].toDouble(), directionJSON["y"].toDouble(), directionJSON["z"].toDouble());

		return object;
	}
}