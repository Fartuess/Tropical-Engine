#include <Light/SpotLightComponent.h>

#include <Scene/Entity.h>

#include <Texture/RenderTexture.h>

namespace TropicalEngine
{

	SpotLightComponent SpotLightComponent::templateObject = SpotLightComponent::InitializeType();

	SpotLightComponent::SpotLightComponent() {}

	SpotLightComponent::SpotLightComponent(Entity* owner, glm::vec3 color, float brightness, float radius, float attenuation,
		float outerConeRadius, float innerConeRadius, bool isCastingShadows) :
		LightComponent(owner, color, brightness, isCastingShadows)
	{
		this->radius = radius;
		this->attenuation = attenuation;
		this->outerConeRadius = outerConeRadius;
		this->innerConeRadius = innerConeRadius;

		InitializeComponentType();
	}

	SpotLightComponent::~SpotLightComponent(void)
	{
		///TODO: implement it.
	}

	SpotLightComponent SpotLightComponent::InitializeType()
	{
		SpotLightComponent& spotLightComponent = *(new SpotLightComponent());
		AssetManager::addAssetType("Spot Light Component", &spotLightComponent);
		return spotLightComponent;
	}

	void SpotLightComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			SetParrentComponentType("Light Component");

			AddParameter("Radius", "Float");
			AddParameter("Attenuation", "Float");
			AddParameter("Outer Radius", "Float");
			AddParameter("Inner Radius", "Float");
		}
	}

	float SpotLightComponent::getRadius()
	{
		return radius;
	}

	void SpotLightComponent::setRadius(float radius)
	{
		this->radius = radius;
		Evaluate();
		if (castingShadows)
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
		if (castingShadows)
			DrawShadows();
	}

	float SpotLightComponent::getInnerConeRadius()
	{
		return innerConeRadius;
	}

	void SpotLightComponent::setInnerConeRadius(float innerConeRadius)
	{
		this->innerConeRadius = innerConeRadius;
	}

	void SpotLightComponent::Evaluate()
	{
		///TODO: implement it.
	}

	void SpotLightComponent::DrawShadows()
	{
		if (shadowmap == nullptr)
		{
			shadowmap = new RenderTexture(owner->name + "_SpotLight_Shadowmap", 1024, 1024);
		}
		///TODO: implement it.

	}

	//QString SpotLightComponent::toXML()
	//{
	//	///TODO: implement it.
	//	return QString(getIndent() + "<SpotLightComponent/>\n");
	//}

	QJsonObject SpotLightComponent::toJSON()
	{
		QJsonObject JSON = LightComponent::toJSON();
		JSON["radius"] = radius;
		JSON["attenuation"] = attenuation;
		JSON["inner cone radius"] = innerConeRadius;
		JSON["outer cone radius"] = outerConeRadius;

		return JSON;
	}

	IDeserializableFromJSON* SpotLightComponent::fromJSON(QJsonObject JSON)
	{
		SpotLightComponent* object = new SpotLightComponent();

		QJsonObject colorJSON = JSON["color"].toObject();
		object->color = glm::vec3(colorJSON["r"].toDouble(), colorJSON["g"].toDouble(), colorJSON["b"].toDouble());
		object->brightness = JSON["brightness"].toDouble();
		object->castingShadows = JSON["casting shadows"].toBool();

		object->radius = JSON["radius"].toDouble();
		object->attenuation = JSON["attenuation"].toDouble();

		object->innerConeRadius = JSON["inner cone radius"].toDouble();
		object->outerConeRadius = JSON["outer cone radius"].toDouble();

		return object;
	}

}