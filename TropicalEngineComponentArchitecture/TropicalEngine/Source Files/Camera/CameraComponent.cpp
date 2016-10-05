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

	CameraComponent::CameraComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar)
		: Component(owner), camera((owner != nullptr ? owner->transform.getTransform(true) : Transform()), targetOffset, up, fov, aspectRatio, zNear, zFar)
	{
		setTarget(targetOffset);
		setUp(up);

		InitializeComponentType();

		//CalculateMatrix();
	}

	CameraComponent CameraComponent::InitializeType()
	{
		CameraComponent& cameraComponent = *(new CameraComponent());
		AssetManager::instance().addAssetType("Camera Component", &cameraComponent);
		return cameraComponent;
	}

	void CameraComponent::InitializeComponentType()
	{
		if (!isComponentTypeUsed(getTypeName()))
		{
			// TODO: ??
		}
	}

	CameraComponent::~CameraComponent(void)
	{
		// TODO: Figure out how to separate it from engine core.
		if (owner != nullptr)
		{
			// TODO: Handle case when destroying camera which is current camera in some scene.
			//Scene* sceneManager = TropicalEngineApplication::instance()->sceneManager;
			//if (sceneManager->getCurrentCamera() == this)
			//{
			//	sceneManager->setCurrentCamera(nullptr);
			//}
		}
	}

	glm::vec3 CameraComponent::getTarget()
	{
		return camera.getTarget();
	}

	void CameraComponent::setTarget(glm::vec3 targetOffset)
	{
		camera.setTarget(targetOffset);
	}

	glm::vec3 CameraComponent::getUp()
	{
		return camera.getUp();
	}

	void CameraComponent::setUp(glm::vec3 up)
	{
		camera.setUp(up);
	}

	float CameraComponent::getFov()
	{
		return camera.getFov();
	}

	void CameraComponent::setFov(float fov)
	{
		camera.setFov(fov);
		//CalculateMatrix();
	}

	float CameraComponent::getAspectRatio()
	{
		return camera.getAspectRatio();
	}

	// TODO: Figure out if Calculation of matrix after every change is required since it can be called once in main Draw method

	void CameraComponent::setAspectRatio(float aspectRatio)
	{
		camera.setAspectRatio(aspectRatio);
		//CalculateMatrix();
	}

	float CameraComponent::getZNear()
	{
		return camera.getZNear();
	}

	void CameraComponent::setZNear(float zNear)
	{
		camera.setZNear(zNear);
		//CalculateMatrix();
	}

	float CameraComponent::getZFar()
	{
		return camera.getZFar();
	}

	void CameraComponent::setZFar(float zFar)
	{
		camera.setZFar(zFar);
		//CalculateMatrix();
	}

	glm::mat4 CameraComponent::getCameraMatrix()
	{
		camera.setTransformReference(this->getOwner()->transform.getTransform(true));
		return camera.getCameraMatrix();
	}

	glm::mat4 CameraComponent::getProjectionMatrix()
	{
		camera.setTransformReference(this->getOwner()->transform.getTransform(true));
		return camera.getProjectionMatrix();
	}

//	void CameraComponent::CalculateMatrix()
//	{
//		camera.setTransformReference(this->getOwner()->transform.getTransform(true));
//	}

	QJsonObject CameraComponent::toJSON()
	{
		QJsonObject JSON = Component::toJSON();
		JSON["camera"] = camera.toJSON();

		return JSON;
	}

	IDeserializableFromJSON* CameraComponent::fromJSON(QJsonObject JSON)
	{
		CameraComponent* cameraComponent = new CameraComponent();
		QJsonObject cameraJSON = JSON["camera"].toObject();
		Camera t;
		Camera camera = *(Camera*)t.fromJSON(cameraJSON);

		// TODO: Finish implementing.
		//cameraComponent->camera = camera;

		return cameraComponent;
	}

}