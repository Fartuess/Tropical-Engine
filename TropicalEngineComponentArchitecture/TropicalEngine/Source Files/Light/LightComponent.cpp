#include <Light/LightComponent.h>
#include <Light/LightController.h>

namespace TropicalEngine
{

	LightComponent::LightComponent() {}

	LightComponent::LightComponent(Entity* owner, glm::vec3 color, float brightness, bool isCastingShadows) :Component(owner)
	{
		this->color = color;
		this->brightness = brightness;
		this->castingShadows = isCastingShadows;
		LightController::instance().lights.append(this);
		Evaluate();
		if (castingShadows)
		{
			LightController::instance().lightShadows.append(this);
			//DrawShadows();
		}

		InitializeComponentType();
	}

	void LightComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			AddParameter("Brightness", "Float");
			AddParameter("Color", "ColorRGB");
		}
	}

	LightComponent::~LightComponent(void)
	{
		if (owner != nullptr)
		{
			LightController::instance().lights.removeOne(this);
			if (castingShadows)
			{
				LightController::instance().lightShadows.removeAll(this);
			}
		}
	}

	bool LightComponent::isCastingShadows()
	{
		return castingShadows;
	}

	void LightComponent::isCastingShadows(bool isCastingShadows)
	{
		if (castingShadows != isCastingShadows)
		{
			if (isCastingShadows == true)
			{
				LightController::instance().lightShadows.append(this);
			}
			else
			{
				LightController::instance().lightShadows.removeAll(this);
			}
			castingShadows = isCastingShadows;
		}
		//DrawShadows();
	}

	void LightComponent::Evaluate()
	{
		// TODO: implement it.
	}

	//void LightComponent::DrawShadows()
	//{
	//	// TODO: implement it.
	//}

	//QString LightComponent::toXML()
	//{
	//	// TODO: implement it.
	//	return QString(getIndent() + "<LightComponent/>\n");
	//}

	QJsonObject LightComponent::toJSON()
	{
		// TODO: implement it.
		QJsonObject JSON = Component::toJSON();
		QJsonObject colorObject = QJsonObject();
		colorObject["r"] = color.r;
		colorObject["g"] = color.g;
		colorObject["b"] = color.b;
		JSON["color"] = colorObject;
		JSON["brightness"] = brightness;
		JSON["casting shadows"] = castingShadows;

		return JSON;
	}

}