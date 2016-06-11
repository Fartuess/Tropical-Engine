#include <Light/AmbientLightComponent.h>

namespace TropicalEngine
{
	AmbientLightComponent AmbientLightComponent::templateObject = AmbientLightComponent::InitializeType();

	AmbientLightComponent::AmbientLightComponent() {}

	AmbientLightComponent::AmbientLightComponent(Entity* owner, glm::vec3 color, float brightness) : LightComponent(owner, color, brightness, false)
	{
		InitializeComponentType();
	}


	AmbientLightComponent::~AmbientLightComponent()
	{
	}

	AmbientLightComponent AmbientLightComponent::InitializeType()
	{
		AmbientLightComponent& ambientLightComponent = *(new AmbientLightComponent());
		AssetManager::instance().addAssetType("Ambient Light Component", &ambientLightComponent);
		return ambientLightComponent;
	}

	void AmbientLightComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			SetParrentComponentType("Light Component");
		}
	}

	QJsonObject AmbientLightComponent::toJSON()
	{
		QJsonObject JSON = LightComponent::toJSON();

		return JSON;
	}

	IDeserializableFromJSON* AmbientLightComponent::fromJSON(QJsonObject JSON)
	{
		AmbientLightComponent* object = new AmbientLightComponent();

		QJsonObject colorJSON = JSON["color"].toObject();
		object->color = glm::vec3(colorJSON["r"].toDouble(), colorJSON["g"].toDouble(), colorJSON["b"].toDouble());
		object->brightness = JSON["brightness"].toDouble();
		object->castingShadows = false;

		return object;
	}
}