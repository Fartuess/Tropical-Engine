#pragma once
#include "LightComponent.h"

class SpotLightComponent : public LightComponent
{
public:
	float attenuation;
	float innerConeRadius;
	
	SpotLightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, float radius = 100.0f, float attenuation = 3.0f,
		float outerConeRadius = 45.0f, float innerConeRadius = 0.0f, bool isCastingShadows = false);
	~SpotLightComponent(void);
	static SpotLightComponent InitializeType();

	float getRadius();
	void setRadius(float radius);
	float getOuterConeRadius();
	void setOuterConeRadius(float outerConeRadius);

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	SpotLightComponent();

	void InitializeComponentType() override;

private:
	float radius;
	float outerConeRadius;

	static SpotLightComponent templateObject;
};

