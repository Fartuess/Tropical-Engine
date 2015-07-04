#pragma once
#include "Light\LightComponent.h"

class DirectionalLightComponent :
	public LightComponent
{
private:
	glm::vec3 direction;

	static DirectionalLightComponent templateObject;
protected:
	DirectionalLightComponent();
public:
	DirectionalLightComponent(Entity* owner, glm::vec3 color, glm::vec3 direction, float brightness = 1.0f, bool isCastingShadows = false);
	~DirectionalLightComponent(void);

	static DirectionalLightComponent InitializeType();
protected:
	void InitializeComponentType() override;
public:
	glm::vec3 getDirection();
	void setDirection(glm::vec3 direction);

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;
	//QString toXML() override;
	QJsonObject toJSON() override;
	IDeserializableFromJSON& fromJSON(QJsonObject JSON) override;
};

