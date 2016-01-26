#include <gtc/matrix_transform.hpp>

#include <QtCore/qdebug.h>

#include <Scene/Entity.h>
#include <Scene/Scene.h>

#include <TropicalEngineApplication.h>

#include <Camera/CameraComponent.h>

namespace TropicalEngine
{

	CameraComponent CameraComponent::templateObject = CameraComponent::InitializeType();

	CameraComponent::CameraComponent() {}

	CameraComponent::CameraComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar) :Component(owner)
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

	CameraComponent CameraComponent::InitializeType()
	{
		CameraComponent& cameraComponent = *(new CameraComponent());
		AssetManager::addAssetType("Camera Component", &cameraComponent);
		return cameraComponent;
	}

	void CameraComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			///TODO: ??
		}
	}

	CameraComponent::~CameraComponent(void)
	{
		///TODO: Figure out how to separate it from engine core.
		if (owner != nullptr)
		{
			/// TODO: Handle case when destroying camera which is current camera in some scene.
			//Scene* sceneManager = TropicalEngineApplication::instance()->sceneManager;
			//if (sceneManager->getCurrentCamera() == this)
			//{
			//	sceneManager->setCurrentCamera(nullptr);
			//}
		}
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
		if (aspectRatio != 0.0f)
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
		cameraMatrix = glm::lookAt(this->getOwner()->transform.getPosition(), this->getOwner()->transform.getPosition() + targetOffset, this->up);
		projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
	}

	//QString CameraComponent::toXML()
	//{
	//	///TODO: implement it.
	//	return QString(getIndent() + "<CameraComponent/>\n");
	//}

	QJsonObject CameraComponent::toJSON()
	{
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

	IDeserializableFromJSON* CameraComponent::fromJSON(QJsonObject JSON)
	{
		CameraComponent* camera = new CameraComponent();

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