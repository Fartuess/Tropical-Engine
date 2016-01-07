#include <Light/PointLightComponent.h>

namespace TropicalEngine
{

	PointLightComponent PointLightComponent::templateObject = PointLightComponent::InitializeType();

	PointLightComponent::PointLightComponent() {}

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

	PointLightComponent PointLightComponent::InitializeType()
	{
		PointLightComponent& pointLightComponent = *(new PointLightComponent());
		AssetManager::addAssetType("Point Light Component", &pointLightComponent);
		return pointLightComponent;
	}

	void PointLightComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
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
		if (castingShadows)
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

	//QString PointLightComponent::toXML()
	//{
	//	///TODO: implement it.
	//	return QString(getIndent() + "<PointLightComponent/>\n");
	//}

	QJsonObject PointLightComponent::toJSON()
	{
		QJsonObject JSON = LightComponent::toJSON();
		JSON["radius"] = radius;
		JSON["attenuation"] = attenuation;

		return JSON;
	}

	IDeserializableFromJSON* PointLightComponent::fromJSON(QJsonObject JSON)
	{
		///TODO: implement this.
		PointLightComponent* object = new PointLightComponent();

		QJsonObject colorJSON = JSON["color"].toObject();
		object->color = glm::vec3(colorJSON["r"].toDouble(), colorJSON["g"].toDouble(), colorJSON["b"].toDouble());
		object->brightness = JSON["brightness"].toDouble();
		object->castingShadows = JSON["casting shadows"].toBool();

		object->radius = JSON["radius"].toDouble();
		object->attenuation = JSON["attenuation"].toDouble();

		return object;
	}

}