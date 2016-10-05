#include <gtc/matrix_transform.hpp>

#include <Camera/Camera.h>


namespace TropicalEngine
{
	//Temp?
	Camera::Camera() : previousTransform()
	{
		//temp
		this->transform = new Transform();
	}

	Camera::Camera(Transform& transform, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar) : previousTransform()
	{
		this->transform = &transform;
		setTarget(targetOffset);
		setUp(up);

		this->fov = fov;
		this->aspectRatio = aspectRatio;
		this->zNear = zNear;
		this->zFar = zFar;
	}

	Camera::~Camera()
	{
	}

	void Camera::setTransformReference(Transform& transform)
	{
		this->transform = &transform;
	}

	glm::vec3 Camera::getTarget()
	{
		return target;
	}

	void Camera::setTarget(glm::vec3 targetOffset)
	{
		target = glm::normalize(targetOffset);
		isEvaluated = false;
	}

	glm::vec3 Camera::getUp()
	{
		return up;
	}

	void Camera::setUp(glm::vec3 up)
	{
		this->up = glm::normalize(up);
		isEvaluated = false;
	}

	float Camera::getFov()
	{
		return fov;
	}

	void Camera::setFov(float fov)
	{
		this->fov = fov;
		isEvaluated = false;
	}

	float Camera::getAspectRatio()
	{
		return aspectRatio;
	}

	void Camera::setAspectRatio(float aspectRatio)
	{
		if (aspectRatio != 0.0f)
		{
			this->aspectRatio = aspectRatio;
			isEvaluated = false;
		}
	}

	float Camera::getZNear()
	{
		return zNear;
	}

	void Camera::setZNear(float zNear)
	{
		this->zNear = zNear;
		isEvaluated = false;
	}

	float Camera::getZFar()
	{
		return zFar;
	}

	void Camera::setZFar(float zFar)
	{
		this->zFar = zFar;
		isEvaluated = false;
	}

	glm::mat4 Camera::getCameraMatrix()
	{
		if (!isEvaluated || *transform != previousTransform)
		{
			CalculateMatrix();
		}
		return cameraMatrix;
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		if (!isEvaluated || *transform != previousTransform)
		{
			CalculateMatrix();
		}
		return projectionMatrix;
	}

	void Camera::CalculateMatrix()
	{
		transform->Evaluate();
		glm::vec3 targetOffset = transform->getFrontVector();
		cameraMatrix = glm::lookAt(transform->getPosition(), transform->getPosition() + targetOffset, this->up);
		projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);

		previousTransform = Transform(*transform);
		previousTransform.setPosition(transform->getPosition());
		previousTransform.setRotation(transform->getRotation());
		previousTransform.setScale(transform->getScale());

		isEvaluated = true;
	}

	QJsonObject Camera::toJSON()
	{
		QJsonObject JSON = QJsonObject();
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

	IDeserializableFromJSON* Camera::fromJSON(QJsonObject JSON)
	{
		Camera* camera = new Camera();

		QJsonObject targetJSON = JSON["target"].toObject();
		camera->setTarget(glm::vec3(targetJSON["x"].toDouble(), targetJSON["y"].toDouble(), targetJSON["z"].toDouble()));

		QJsonObject upJSON = JSON["up"].toObject();
		camera->setUp(glm::vec3(upJSON["x"].toDouble(), upJSON["y"].toDouble(), upJSON["z"].toDouble()));

		camera->fov = JSON["fov"].toDouble();
		camera->aspectRatio = JSON["aspect ratio"].toDouble();
		camera->zNear = JSON["Z near"].toDouble();
		camera->zFar = JSON["Z far"].toDouble();

		camera->CalculateMatrix();

		return camera;
	}
}