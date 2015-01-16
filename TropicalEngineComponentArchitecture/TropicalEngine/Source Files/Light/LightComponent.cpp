#include "Light\LightComponent.h"
#include "Light\LightController.h"

#include "TropicalEngineApplication.h"

LightComponent::LightComponent(Entity* owner, glm::vec3 color, float brightness, bool isCastingShadows):Component(owner)
{
	this->color = color;
	this->brightness = brightness;
	this->castingShadows = isCastingShadows;
	TropicalEngineApplication::instance()->lightController->lights.append(this);
	Evaluate();
	if(castingShadows)
		DrawShadows();

	InitializeComponentType();
}

void LightComponent::InitializeComponentType()
{
	if(!isComponentTypeUsed(getName()))
	{
		AddParameter("Brightness", "Float");
		AddParameter("Color", "ColorRGB");
	}
}

LightComponent::~LightComponent(void)
{
	TropicalEngineApplication::instance()->lightController->lights.removeOne(this);
}

bool LightComponent::isCastingShadows()
{
	return castingShadows;
}

void LightComponent::isCastingShadows(bool isCastingShadows)
{
	castingShadows = true;
	DrawShadows();
}

void LightComponent::Evaluate()
{
	///TODO: implement it.
}

void LightComponent::DrawShadows()
{
	///TODO: implement it.
}

QString LightComponent::COMPONENTGETNAME("Light Component");

QString LightComponent::toXML()
{
	///TODO: implement it.
	return QString(getIndent() + "<LightComponent/>\n");
}

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