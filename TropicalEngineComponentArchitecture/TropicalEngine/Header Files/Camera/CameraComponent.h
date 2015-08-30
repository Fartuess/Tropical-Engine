#pragma once
#include <glm.hpp>

#include <Component/Component.h>

/**
  * Camera Component.
  */
class CameraComponent : public Component
{
public:
	/**
	  * \brief Camera component costructor.
	  *
	  * @param owner Entity object to which CameraComponent will be attached to.
	  * @param targetOffset defines direction where camera is looking at.
	  * @param up vector defining camera roll.
	  * @param fov field of view of the camera.
	  * @param aspectRatio width to height ratio of the camera.
	  * @param zNear Near clipping plane distance.
	  * @param zFar Far clipping plane distance.
	  */
	CameraComponent(Entity* owner, glm::vec3 targetOffset, glm::vec3 up, float fov, float aspectRatio, float zNear, float zFar);

	/**
	  * \brief Default destructor
	  */
	~CameraComponent(void);
	
	/**
	  * \brief Gets target offset of the CameraComponent.
	  *
	  * @return Vector describing target offset of CameraComponent
	  */
	glm::vec3 getTarget();

	/**
	  * \brief Sets direction where CameraComponent is looking.
	  *
	  * @param targetOffset Position offset describing direction where CameraComponent is looking at.
	  */
	void setTarget(glm::vec3 targetOffset);

	/**
	  * \brief Gets Up Vector of CameraComponent.
	  *
	  * @return Up Vector of the CamerComponent.
	  */
	glm::vec3 getUp();

	/**
	  * \brief Sets Up Vector of CameraComponent.
	  *
	  * Sets roll of the camera by defining Up vector.
	  * @param Up Vector defining up direction of the camera.
	  */
	void setUp(glm::vec3 up);
	
	/**
	  * \brief Gets Field of View of CameraComponent.
	  *
	  * @return Field of View value.
	  */
	float getFov();

	/**
	  * \brief Sets Field of View of CameraComponent.
	  *
	  * @param fov Field of View value.
	  */
	void setFov(float fov);

	/**
	  * \brief Gets Aspect ratio of CameraComponent.
	  *
	  * Returns width to height proportions of the CameraComponent.
	  * @return Aspect Ratio of the CameraComponent.
	  */
	float getAspectRatio();

	/**
	  * \brief Sets Aspect ratio of CameraComponent.
	  *
	  * Sets width to height proportions of the CameraComponent.
	  * @param aspectRatio Aspect Ratio of the CameraComponent.
	  */
	void setAspectRatio(float aspectRatio);

	/**
	  * \brief Gets Near Clipping Plane distance.
	  *
	  * @return Near Clipping Plane distance.
	  */
	float getZNear();

	/**
	  * \brief Sets Near Clipping Plane distance.
	  *
	  * @param zNear Near Clipping Plane distance.
	  */
	void setZNear(float zNear);

	/**
	  * \brief Gets Far Clipping Plane distance.
	  *
	  * @return Far Clipping Plane distance.
	  */
	float getZFar();

	/**
	  * \brief Sets Far Clipping Plane distance.
	  *
	  * @param zFar Far Clipping Plane Distance.
	  */
	void setZFar(float zFar);

	/**
	  * \brief Gets Camera Matrix.
	  *
	  * Gets Camera Matrix without Projection.
	  * @return 4x4 Camera Martix.
	  */
	glm::mat4 getCameraMatrix();

	/**
	  * \brief Gets Projection Matrix.
	  *
	  * Gets Projection Matrix without Camera Matrix.
	  * @return 4x4 Projection Matrix.2
	  */
	glm::mat4 getProjectionMatrix();

	/**
	  * \brief Updates Camera Matrix and Projection matrices.
	  *
	  * Mostly for internal use in engine part of code.
	  */
	void CalculateMatrix();

	/**
	  * \brief Returns name of the type.
	  *
	  * @return "Camera Component"
	  */
	QString getTypeName() override;

	/**
	  * \brief Serializes CameraComponent to JSON object.
	  *
	  * @return Result of serialization.
	  */
	QJsonObject toJSON() override;

	/**
	  * \brief Deserializes CameraComponent from JSON object.
	  *
	  * @param JSON JSON object to deserialize from.
	  * @return CameraComponent object.
	  */
	IDeserializableFromJSON* fromJSON(QJsonObject JSON) override;

protected:
	/**
	  * \brief Simple Constructor used to create CameraComponent instance while serializing.
	  */
	CameraComponent();

	/**
	  * \brief Initialized type in global typemap.
	  */
	void InitializeComponentType() override;

private:
	glm::vec3 target;
	glm::vec3 up;
	glm::mat4 cameraMatrix;
	glm::mat4 projectionMatrix;

	float fov;
	float aspectRatio;
	float zNear;
	float zFar;

	static CameraComponent templateObject;
	static CameraComponent InitializeType();
};

