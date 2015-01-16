#include <gtc\matrix_transform.hpp>
#include "Camera/CameraComponent.h"
#include "Scene/Entity.h"

#include <QtCore\qdebug.h>

CameraComponent::CameraComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar):Component(owner)
{
	setTarget(targetOffset);
	setUp(up);

	this->fov = fov;
	this->aspectRatio = aspectRatio;
	this->zNear = zNear;
	this->zFar = zFar;

	InitializeComponentType();

	CalculateMatrix();
}

void CameraComponent::InitializeComponentType()
{
	if(!isComponentTypeUsed(getName()))
	{
		
	}
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

void CameraComponent::setUp(glm::vec3 up)
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

///TODO: Figure out if Calculation of matrix after every change is required since it can be called once in main Draw method

void CameraComponent::setAspectRatio(float aspectRatio)
{
	if(aspectRatio != 0.0f)
	{
		this->aspectRatio = aspectRatio;
		CalculateMatrix();
	}
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

//glm::mat4x4 CameraComponent::getMatrix()
//{
//	return cameraMatrix;
//}

glm::mat4 CameraComponent::getCameraMatrix()
{
	return cameraMatrix;
}

glm::mat4 CameraComponent::getProjectionMatrix()
{
	return projectionMatrix;
}

void CameraComponent::CalculateMatrix()
{
	glm::vec3 targetOffset = owner->transform.getFront();
	//qDebug() << QString(QString::number(targetOffset.x) + ", " + QString::number(targetOffset.y) + ", " + QString::number(targetOffset.z));
	cameraMatrix = glm::lookAt(this->getOwner()->transform.getPosition(), this->getOwner()->transform.getPosition() + targetOffset, this->up);
	//qDebug() << QString::number(glm::length(targetOffset));
	//qDebug() << QString(QString::number(this->getOwner()->transform.getPosition().x) + ", " + QString::number(this->getOwner()->transform.getPosition().y) + ", " + QString::number(this->getOwner()->transform.getPosition().z));
	projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);

	//cameraMatrix = perspectiveProjection * cameraProjection;
}

QString CameraComponent::COMPONENTGETNAME("Camera Component");

QString CameraComponent::toXML()
{
	///TODO: implement it.
	return QString(getIndent() + "<CameraComponent/>\n");
}

QJsonObject CameraComponent::toJSON()
{
	///TODO: implement it.
	QJsonObject JSON = Component::toJSON();
	QJsonObject targetObject = QJsonObject();
	targetObject["x"] = target.x;
	targetObject["y"] = target.y;
	targetObject["z"] = target.z;
	JSON["target"] = targetObject;
	QJsonObject upObject = QJsonObject();
	upObject["x"] = up.x;
	upObject["y"] = up.y;
	upObject["z"] = up.z;
	JSON["up"] = upObject;
	JSON["fov"] = fov;
	JSON["aspect ratio"] = aspectRatio;
	JSON["Z near"] = zNear;
	JSON["Z far"] = zFar;

	return JSON;
}