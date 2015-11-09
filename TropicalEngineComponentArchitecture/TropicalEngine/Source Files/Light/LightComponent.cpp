#include <Light/LightComponent.h>
#include <Light/LightController.h>

#include <TropicalEngineApplication.h>

LightComponent::LightComponent() {}

LightComponent::LightComponent(Entity* owner, glm::vec3 color, float brightness, bool isCastingShadows):Component(owner)
{
	this->color = color;
	this->brightness = brightness;
	this->castingShadows = isCastingShadows;
	TropicalEngineApplication::instance()->lightController->lights.append(this);
	Evaluate();
	if (castingShadows)
	{
		TropicalEngineApplication::instance()->lightController->lightShadows.append(this);
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
		TropicalEngineApplication::instance()->lightController->lights.removeOne(this);
		if (castingShadows)
		{
			TropicalEngineApplication::instance()->lightController->lightShadows.removeAll(this);
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
			TropicalEngineApplication::instance()->lightController->lightShadows.append(this);
		}
		else
		{
			TropicalEngineApplication::instance()->lightController->lightShadows.removeAll(this);
		}
		castingShadows = isCastingShadows;
	}
	//DrawShadows();
}

void LightComponent::Evaluate()
{
	///TODO: implement it.
}

//void LightComponent::DrawShadows()
//{
//	///TODO: implement it.
//}

//QString LightComponent::toXML()
//{
//	///TODO: implement it.
//	return QString(getIndent() + "<LightComponent/>\n");
//}

QJsonObject LightComponent::toJSON()
{
	///TODO: implement it.
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