#pragma once
#include <glm.hpp>

#include <Component/Component.h>

#define MAX_POINT_LIGHT 2

///TODO: Should it be an abstract class?
class LightComponent : public Component
{
public:
	glm::vec3 color;
	float brightness;

	LightComponent(Entity* owner, glm::vec3 color, float brightness = 1.0f, bool isCastingShadows = false);
	~LightComponent(void);

	bool isCastingShadows();
	void isCastingShadows(bool isCastingShadows);

	void Evaluate();
	void DrawShadows();

	QString getTypeName() override;

	QJsonObject toJSON() override;

protected:
	bool castingShadows;

	LightComponent();

	void InitializeComponentType() override;
};