#pragma once
#include "LightComponent.h"

class DirectionalLightComponent : public LightComponent
{

public:
	DirectionalLightComponent(Entity* owner, glm::vec3 color, glm::vec3 direction, float brightness = 1.0f, bool isCastingShadows = false);
	~DirectionalLightComponent(void);

	static DirectionalLightComponent InitializeType();

	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	DirectionalLightComponent();
	void InitializeComponentType() override;

private:
	glm::vec3 direction;

	static DirectionalLightComponent templateObject;
};

