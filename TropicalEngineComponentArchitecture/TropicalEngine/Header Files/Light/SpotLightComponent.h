#pragma once
#include "Light\LightComponent.h"

class SpotLightComponent :
	public LightComponent
{
private:
	float radius;
	float outerConeRadius;
public:
	float attenuation;
	float innerConeRadius;

	SpotLightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f,
		float outerConeRadius = 45.0f, float innerConeRadius = 0.0f, bool isCastingShadows = false);
	~SpotLightComponent(void);
protected:
	void InitializeComponentType() override;
public:
	float getRadius();
	void setRadius(float radius);
	float getOuterConeRadius();
	void setOuterConeRadius(float outerConeRadius);

	void Evaluate();
	void DrawShadows();

	QString getName() override;
	QString toXML() override;
	QJsonObject toJSON() override;
};
