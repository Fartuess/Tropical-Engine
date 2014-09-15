#pragma once
#include "cameracomponent.h"

class TempPlayerComponent :
	public CameraComponent
{
public:
	TempPlayerComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar);
	~TempPlayerComponent(void);

	void Update();

	QString getName() override;
};