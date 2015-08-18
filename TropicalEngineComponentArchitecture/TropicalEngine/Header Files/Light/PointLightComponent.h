#pragma once

#include "LightComponent.h"

class PointLightComponent : public LightComponent
{
public:
	float attenuation;

	PointLightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f, bool isCastingShadows = false);
	~PointLightComponent(void);

	static PointLightComponent InitializeType();

	float getRadius();
	void setRadius(float radius);

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	PointLightComponent();

	void InitializeComponentType() override;

private:
	float radius;

	static PointLightComponent templateObject;
};

