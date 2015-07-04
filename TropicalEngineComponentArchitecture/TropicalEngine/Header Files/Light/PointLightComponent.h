#pragma once
#include "Light\LightComponent.h"

class PointLightComponent :
	public LightComponent
{
private:
	float radius;
public:
	float attenuation;
private:
	static PointLightComponent templateObject;
protected:
	PointLightComponent();
public:
	PointLightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f, bool isCastingShadows = false);
	~PointLightComponent(void);

	static PointLightComponent InitializeType();
protected:
	void InitializeComponentType() override;
public:
	float getRadius();
	void setRadius(float radius);

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;
	//QString toXML() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON& fromJSON(QJsonObject JSON) override;
};

