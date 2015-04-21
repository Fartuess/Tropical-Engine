#pragma once
#include <glm.hpp>
#include "Component\Component.h"

class CameraComponent :
	public Component
{
private:
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 cameraMatrix;
	glm::mat4 projectionMatrix;

	float fov;
	float aspectRatio;
	float zNear;
	float zFar;
public:
	CameraComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar);
	~CameraComponent(void);
protected:
	void InitializeComponentType() override;
public:
	glm::vec3 getTarget();
	void setTarget(glm::vec3 targetOffset);
	glm::vec3 getUp();
	void setUp(glm::vec3 Up);

	float getFov();
	void setFov(float fov);
	float getAspectRatio();
	void setAspectRatio(float aspectRatio);
	float getZNear();
	void setZNear(float zNear);
	float getZFar();
	void setZFar(float zFar);

	glm::mat4 getCameraMatrix();
	glm::mat4 getProjectionMatrix();
	void CalculateMatrix();

	QString getTypeName() override;
	QString toXML() override;
	QJsonObject toJSON() override;
};

