#include <gtc\matrix_transform.hpp>
#include "CameraComponent.h"
#include "Entity.h"


CameraComponent::CameraComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar):Component(owner)
{
	setTarget(targetOffset);
	setUp(up);

	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->zNear = zNear;
	this->zFar = zFar;

	CalculateMatrix();
}


CameraComponent::~CameraComponent(void)
{
	///TODO: implement it.
}

glm::vec3 CameraComponent::getTarget()
{
	return target;
}

void CameraComponent::setTarget(glm::vec3 targetOffset)
{
	target = glm::normalize(targetOffset);
}

glm::vec3 CameraComponent::getUp()
{
	return up;
}

void CameraComponent::setUp(glm::vec3 Up)
{
	this->up = glm::normalize(up);
}

float CameraComponent::getFov()
{
	return fov;
}

void CameraComponent::setFov(float fov)
{
	this->fov = fov;
	CalculateMatrix();
}

float CameraComponent::getAspectRatio()
{
	return aspectRatio;
}

void CameraComponent::setAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
	CalculateMatrix();
}

float CameraComponent::getZNear()
{
	return zNear;
}

void CameraComponent::setZNear(float zNear)
{
	this->zNear = zNear;
	CalculateMatrix();
}

float CameraComponent::getZFar()
{
	return zFar;
}

void CameraComponent::setZFar(float zFar)
{
	this->zFar = zFar;
	CalculateMatrix();
}


glm::mat4x4 CameraComponent::getMatrix()
{
	return cameraMatrix;
}

void CameraComponent::CalculateMatrix()
{
	///TODO: implement it.
	glm::vec3 up2 = glm::cross(up, target);
	glm::vec3 target2 = glm::cross(target, up2);

	glm::mat4x4 cameraProjection = glm::lookAt(this->getOwner()->transform.getPosition(), this->getOwner()->transform.getPosition() + this->target, this->up);
	glm::mat4x4 perspectiveProjection = glm::perspective(fov, aspectRatio, zNear, zFar);

	cameraMatrix = perspectiveProjection * cameraProjection;

	//cameraMatrix[0][0] = up2.x; cameraMatrix[0][1] = up2.y; cameraMatrix[0][2] = up2.z; cameraMatrix[0][3] = 0.0f;
	//cameraMatrix[1][0] = target2.x; cameraMatrix[1][1] = target2.y; cameraMatrix[1][2] = target2.z; cameraMatrix[1][3] = 0.0f;
	//cameraMatrix[2][0] = target.x; cameraMatrix[2][1] = target.y; cameraMatrix[2][2] = target.z; cameraMatrix[2][3] = 0.0f;
	//cameraMatrix[3][0] = 0.0f; cameraMatrix[3][1] = 0.0f; cameraMatrix[3][2] = 0.0f; cameraMatrix[3][3] = 1.0f;
}
